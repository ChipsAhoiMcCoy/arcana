// The updater (updater.h). One worker thread at a time does the network and file work; the game thread reads its
// state for the settings menu and speaks what it found (tick).
//
// Where things go: <the mod's folder>\update\ (Win64\Arcana\update for a Steam install):
//   arcana-<v>.zip.part -> arcana-<v>.zip   the download, checked against the SHA-256 GitHub computed on upload
//   new\                                     the zip unpacked by Windows' own tar.exe (it reads zip)
//   ready                                    the version in new\, written last; the proxy installs it next start
//   result                                   what the proxy did ("installed 0.9.0"), read and removed here
// %LOCALAPPDATA%\Arcana\update.ini: "announced=<v>", the newest version the startup check has spoken of (once each).
// Dev: P3A_UPDATE_VERSION=0.6.0 pretends to be that release (a dev build has no version and never checks);
// P3A_UPDATE_URL replaces the release list's address (a local test server: http:// works too). /update drives it.
#include "updater.h"

#include <windows.h>
#include <bcrypt.h>
#include <winhttp.h>

#include <atomic>
#include <cstdio>
#include <format>
#include <functional>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

#include "core/release_pick.h"
#include "core/strings.h"
#include "core/version.h"
#include "devserver.h"
#include "keys.h"
#include "log.h"
#include "mod.h"
#include "paths.h"
#include "proxy/apply_update.h"
#include "settings.h"
#include "speech.h"
#include "voice.h"

namespace p3a::updater {
namespace fs = update_apply;   // exists, remove_tree, read_small, write_small

static const wchar_t* kReleases = L"https://api.github.com/repos/ChipsAhoiMcCoy/arcana/releases?per_page=20";

enum class St { NoVersion, Idle, Checking, Current, CheckFailed, Available, Downloading, Unpacking, Ready,
                FailNetwork, FailChecksum, FailWrite, FailUnpack };
enum class Ev { StartupFound, CheckDone, Downloaded, DownloadFailed };

static std::mutex g_m;   // guards everything below it
static St g_st = St::NoVersion;
static core::Release g_rel;          // the newer release, once one is known
static int g_pct = 0;                // the download's progress
static std::vector<Ev> g_events;     // for tick to speak
static std::string g_proxy_result;   // the proxy's line at this start, for tick

static std::string g_version;        // this build's ("0.8.0"), empty in a dev build
static std::thread g_worker;
static std::atomic<bool> g_busy{false}, g_stop{false};

static std::wstring wide(const std::string& s) {
  if (s.empty()) return {};
  int n = MultiByteToWideChar(CP_UTF8, 0, s.data(), (int)s.size(), nullptr, 0);
  std::wstring w((size_t)n, L'\0');
  MultiByteToWideChar(CP_UTF8, 0, s.data(), (int)s.size(), w.data(), n);
  return w;
}
static std::string env(const wchar_t* name) {
  wchar_t buf[512];
  DWORD n = GetEnvironmentVariableW(name, buf, 512);
  if (n == 0 || n >= 512) return {};
  return log::utf8(std::u16string(buf, buf + n));
}
static std::wstring update_dir() {
  std::wstring d = paths::dir_w();   // with its trailing backslash
  return d + L"update";
}
static std::wstring announced_file() {
  std::wstring p = log::path();
  return p.substr(0, p.find_last_of(L'\\') + 1) + (env_flag(L"P3A_NOFOCUS") ? L"update-dev.ini" : L"update.ini");
}
static std::string announced() {
  std::string s = fs::read_small(announced_file());
  if (!s.starts_with("announced=")) return {};
  s = s.substr(10);
  while (!s.empty() && (s.back() == '\n' || s.back() == '\r')) s.pop_back();
  return s;
}

static void set_state(St st) { std::lock_guard l(g_m); g_st = st; }
static void push(Ev e) { std::lock_guard l(g_m); g_events.push_back(e); }

// ---- the network: one GET, its body handed to `sink` chunk by chunk (false from it stops). The HTTP status, or 0
// when the request never got an answer. Redirects are followed (a release asset's address sends you to GitHub's
// file host). ----
static int http_get(const std::wstring& url, bool api, const std::function<bool(const char*, size_t)>& sink) {
  wchar_t host[256] = {}, path[2048] = {}, extra[2048] = {};
  URL_COMPONENTS uc{};
  uc.dwStructSize = sizeof uc;
  uc.lpszHostName = host; uc.dwHostNameLength = 256;
  uc.lpszUrlPath = path; uc.dwUrlPathLength = 2048;
  uc.lpszExtraInfo = extra; uc.dwExtraInfoLength = 2048;
  if (!WinHttpCrackUrl(url.c_str(), 0, 0, &uc)) return 0;
  const bool secure = uc.nScheme == INTERNET_SCHEME_HTTPS;
  HINTERNET ses = WinHttpOpen(L"Arcana-updater", WINHTTP_ACCESS_TYPE_AUTOMATIC_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
  if (!ses) ses = WinHttpOpen(L"Arcana-updater", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
  if (!ses) return 0;
  WinHttpSetTimeouts(ses, 10000, 10000, 15000, 15000);
  int status = 0;
  HINTERNET con = WinHttpConnect(ses, host, uc.nPort, 0);
  HINTERNET req = con ? WinHttpOpenRequest(con, L"GET", (std::wstring(path) + extra).c_str(), nullptr, WINHTTP_NO_REFERER,
                                           WINHTTP_DEFAULT_ACCEPT_TYPES, secure ? WINHTTP_FLAG_SECURE : 0)
                      : nullptr;
  if (req) {
    const wchar_t* headers = api ? L"Accept: application/vnd.github+json\r\nX-GitHub-Api-Version: 2022-11-28\r\n" : WINHTTP_NO_ADDITIONAL_HEADERS;
    if (WinHttpSendRequest(req, headers, api ? (DWORD)-1L : 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0) && WinHttpReceiveResponse(req, nullptr)) {
      DWORD code = 0, len = sizeof code;
      WinHttpQueryHeaders(req, WINHTTP_QUERY_STATUS_CODE | WINHTTP_QUERY_FLAG_NUMBER, WINHTTP_HEADER_NAME_BY_INDEX, &code, &len, WINHTTP_NO_HEADER_INDEX);
      status = (int)code;
      if (status == 200) {
        std::vector<char> buf(64 * 1024);
        for (;;) {
          DWORD got = 0;
          if (g_stop || !WinHttpReadData(req, buf.data(), (DWORD)buf.size(), &got)) { status = 0; break; }
          if (got == 0) break;   // the whole body
          if (!sink(buf.data(), got)) { status = 0; break; }
        }
      }
    }
    WinHttpCloseHandle(req);
  }
  if (con) WinHttpCloseHandle(con);
  WinHttpCloseHandle(ses);
  return status;
}

// ---- the jobs, on the worker ----
static void check_job(bool startup) {
  std::string json;
  std::string url_env = env(L"P3A_UPDATE_URL");
  const std::wstring url = url_env.empty() ? std::wstring(kReleases) : wide(url_env);
  int status = http_get(url, true, [&](const char* d, size_t n) { json.append(d, n); return json.size() < 8 * 1024 * 1024; });
  if (status != 200) {
    log::writef("update: the release list did not come (HTTP {})", status);
    set_state(St::CheckFailed);
    if (!startup) push(Ev::CheckDone);
    return;
  }
  auto rel = core::pick_release(json, core::parse_version(g_version.c_str()));
  {
    std::lock_guard l(g_m);
    if (rel) { g_rel = *rel; g_st = St::Available; }
    else g_st = St::Current;
  }
  log::writef("update: this is {}; {}", g_version, rel ? std::format("{} is out ({} bytes)", rel->version, rel->size) : std::string("no newer release"));
  if (!startup) push(Ev::CheckDone);
  else if (rel && announced() != rel->version) push(Ev::StartupFound);
}

static bool fail(St st, const char* why) {
  log::writef("update: {}", why);
  set_state(st);
  push(Ev::DownloadFailed);
  return false;
}

static bool download_job() {
  core::Release rel;
  { std::lock_guard l(g_m); rel = g_rel; g_pct = 0; g_st = St::Downloading; }
  const std::wstring dir = update_dir(), fresh = dir + L"\\new", ready = dir + L"\\ready";
  const std::wstring zip = dir + L"\\arcana-" + wide(rel.version) + L".zip", part = zip + L".part";
  CreateDirectoryW(dir.c_str(), nullptr);
  DeleteFileW(ready.c_str());   // an older staged update gives way
  HANDLE f = CreateFileW(part.c_str(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
  if (f == INVALID_HANDLE_VALUE) return fail(St::FailWrite, std::format("cannot write in the mod's folder (error {})", GetLastError()).c_str());

  BCRYPT_ALG_HANDLE alg = nullptr;
  BCRYPT_HASH_HANDLE hash = nullptr;
  bool hashing = BCRYPT_SUCCESS(BCryptOpenAlgorithmProvider(&alg, BCRYPT_SHA256_ALGORITHM, nullptr, 0)) &&
                 BCRYPT_SUCCESS(BCryptCreateHash(alg, &hash, nullptr, 0, nullptr, 0, 0));
  uint64_t got = 0;
  bool wrote = true;
  int status = http_get(wide(rel.zip_url), false, [&](const char* d, size_t n) {
    DWORD w = 0;
    if (!WriteFile(f, d, (DWORD)n, &w, nullptr) || w != n) { wrote = false; return false; }
    if (hashing) BCryptHashData(hash, (PUCHAR)d, (ULONG)n, 0);
    got += n;
    if (rel.size) { std::lock_guard l(g_m); g_pct = (int)(got * 100 / rel.size); }
    return true;
  });
  CloseHandle(f);
  unsigned char digest[32] = {};
  if (hashing) BCryptFinishHash(hash, digest, 32, 0);
  if (hash) BCryptDestroyHash(hash);
  if (alg) BCryptCloseAlgorithmProvider(alg, 0);
  if (!wrote) { DeleteFileW(part.c_str()); return fail(St::FailWrite, "a write to the download failed (disk full?)"); }
  if (status != 200) { DeleteFileW(part.c_str()); return fail(St::FailNetwork, std::format("the download stopped (HTTP {}, {} bytes)", status, got).c_str()); }
  if (!hashing || core::hex_digest(digest) != rel.sha256 || (rel.size && got != rel.size)) {
    DeleteFileW(part.c_str());
    return fail(St::FailChecksum, std::format("the download does not match: {} bytes, sha256 {}, expected {}", got, hashing ? core::hex_digest(digest) : "?", rel.sha256).c_str());
  }
  DeleteFileW(zip.c_str());
  if (!MoveFileW(part.c_str(), zip.c_str())) return fail(St::FailWrite, "cannot rename the download");
  log::writef("update: downloaded {} ({} bytes, checksum matches)", rel.version, got);

  // Unpack with Windows' tar (Windows 10 1803 and later), no window.
  set_state(St::Unpacking);
  if (fs::exists(fresh)) fs::remove_tree(fresh);
  if (!CreateDirectoryW(fresh.c_str(), nullptr)) return fail(St::FailWrite, "cannot make the unpack folder");
  wchar_t sys[MAX_PATH];
  GetSystemDirectoryW(sys, MAX_PATH);
  const std::wstring tar = std::wstring(sys) + L"\\tar.exe";
  std::wstring cmd = L"\"" + tar + L"\" -xf \"" + zip + L"\" -C \"" + fresh + L"\"";
  STARTUPINFOW si{};
  si.cb = sizeof si;
  PROCESS_INFORMATION pi{};
  if (!CreateProcessW(tar.c_str(), cmd.data(), nullptr, nullptr, FALSE, CREATE_NO_WINDOW, nullptr, nullptr, &si, &pi))
    return fail(St::FailUnpack, std::format("tar.exe did not start (error {})", GetLastError()).c_str());
  while (WaitForSingleObject(pi.hProcess, 200) == WAIT_TIMEOUT)
    if (g_stop) { TerminateProcess(pi.hProcess, 1); break; }
  DWORD code = 1;
  GetExitCodeProcess(pi.hProcess, &code);
  CloseHandle(pi.hThread);
  CloseHandle(pi.hProcess);
  if (code != 0 || !fs::exists(fresh + L"\\Arcana\\arcana.dll") || !fs::exists(fresh + L"\\dsound.dll")) {
    fs::remove_tree(fresh);
    return fail(St::FailUnpack, std::format("unpacking failed (tar exit {})", code).c_str());
  }
  fs::write_small(ready, rel.version + "\n");
  log::writef("update: {} is ready; the proxy installs it at the next start", rel.version);
  set_state(St::Ready);
  push(Ev::Downloaded);
  return true;
}

static bool start(std::function<void()> job) {
  if (g_busy.exchange(true)) return false;
  if (g_worker.joinable()) g_worker.join();
  g_worker = std::thread([job = std::move(job)] {
    job();
    g_busy = false;
  });
  return true;
}

// ---- the game thread ----
void install() {
#ifdef P3A_VERSION
  g_version = P3A_VERSION;
#endif
  if (std::string v = env(L"P3A_UPDATE_VERSION"); !v.empty()) g_version = v;
  if (!core::parse_version(g_version.c_str()).ok) g_version.clear();

  const std::wstring dir = update_dir();
  if (std::string r = fs::read_small(dir + L"\\result"); !r.empty()) {
    while (!r.empty() && (r.back() == '\n' || r.back() == '\r')) r.pop_back();
    log::writef("update: at this start the proxy said: {}", r);
    std::lock_guard l(g_m);
    g_proxy_result = r;
    DeleteFileW((dir + L"\\result").c_str());
  }

  dev::route("/update", [](const dev::Request& r, int&) {
    // ?activate=1 (Enter on the status row) | ?notes=1 (read the notes) | nothing: the state
    bool act = dev::has(r, "activate"), notes = dev::has(r, "notes");
    return dev::on_game([=] {
      if (act) activate();
      if (notes) read_notes();
      std::lock_guard l(g_m);
      return std::format("version={} state={} pct={} release={} zip={} sha256={}\n", g_version, (int)g_st, g_pct, g_rel.version, g_rel.zip_url, g_rel.sha256);
    });
  }, "?activate=1 ?notes=1 the updater's state");

  if (g_version.empty()) { log::write("update: a dev build (no version): no checks"); return; }
  set_state(St::Idle);
  // An update downloaded last session that the proxy has not installed yet (or could not): wait for the next start.
  core::Version staged = core::parse_version(fs::read_small(dir + L"\\ready").c_str());
  if (staged.ok && core::newer(staged, core::parse_version(g_version.c_str()))) {
    std::lock_guard l(g_m);
    g_rel.version = std::format("{}.{}.{}", staged.part[0], staged.part[1], staged.part[2]);
    g_st = St::Ready;
    return;
  }
  if (settings::on(settings::CheckUpdates)) {
    set_state(St::Checking);
    start([] { check_job(true); });
  }
}

void shutdown() {
  g_stop = true;
  if (g_worker.joinable()) g_worker.join();
}

void tick() {
  std::vector<Ev> evs;
  std::string proxy;
  {
    std::lock_guard l(g_m);
    if (g_events.empty() && g_proxy_result.empty()) return;
    evs.swap(g_events);
    proxy.swap(g_proxy_result);
  }
  if (proxy.starts_with("installed ")) speech::speak(strings::fmt(strings::kUpdateInstalledFmt, proxy.substr(10)), false);
  else if (proxy.starts_with("failed")) speech::speak(strings::kUpdateInstallFailed.c_str(), false);
  for (Ev e : evs) {
    switch (e) {
      case Ev::StartupFound: {
        std::string v;
        { std::lock_guard l(g_m); v = g_rel.version; }
        std::string line = keys::fill(strings::kUpdateAnnounceFmt());
        speech::speak(std::vformat(line, std::make_format_args(v)), false);
        fs::write_small(announced_file(), "announced=" + v + "\n");
        break;
      }
      case Ev::CheckDone: case Ev::Downloaded: case Ev::DownloadFailed: speech::speak(status_line(), false); break;
    }
  }
}

std::string status_line() {
  std::lock_guard l(g_m);
  const std::string& v = g_rel.version;
  switch (g_st) {
    case St::NoVersion: return strings::kUpdateDevBuild.c_str();
    case St::Idle: return strings::fmt(strings::kUpdateUncheckedFmt, g_version);
    case St::Checking: return strings::kUpdateChecking.c_str();
    case St::Current: return strings::fmt(strings::kUpdateCurrentFmt, g_version);
    case St::CheckFailed: return strings::kUpdateCheckFailed.c_str();
    case St::Available: return strings::fmt(strings::kUpdateAvailableFmt, v);
    case St::Downloading: return strings::fmt(strings::kUpdateDownloadingFmt, v, g_pct);
    case St::Unpacking: return strings::fmt(strings::kUpdateUnpackingFmt, v);
    case St::Ready: return strings::fmt(strings::kUpdateReadyFmt, v);
    case St::FailNetwork: return strings::kUpdateFailedNetwork.c_str();
    case St::FailChecksum: return strings::kUpdateFailedChecksum.c_str();
    case St::FailWrite: return strings::kUpdateFailedWrite.c_str();
    case St::FailUnpack: return strings::kUpdateFailedUnpack.c_str();
  }
  return {};
}

void activate() {
  St st;
  std::string v;
  { std::lock_guard l(g_m); st = g_st; v = g_rel.version; }
  switch (st) {
    case St::Idle: case St::Current: case St::CheckFailed:
      set_state(St::Checking);   // before the worker can finish
      if (!start([] { check_job(false); })) { set_state(st); return; }
      voice::play_system_sound(voice::CueDecide);
      speech::speak(strings::kUpdateChecking.c_str(), true);
      return;
    case St::Available: case St::FailNetwork: case St::FailChecksum: case St::FailWrite: case St::FailUnpack:
      set_state(St::Downloading);
      if (!start([] { download_job(); })) { set_state(st); return; }
      voice::play_system_sound(voice::CueDecide);
      speech::speak(strings::fmt(strings::kUpdateDownloadStartFmt, v), true);
      return;
    default: speech::speak(status_line(), true); return;
  }
}

bool has_notes() {
  std::lock_guard l(g_m);
  return !g_rel.notes.empty() && g_st != St::Current && g_st != St::Checking;
}

std::string notes_title() {
  std::lock_guard l(g_m);
  return strings::fmt(strings::kUpdateNotesFmt, g_rel.version);
}

void read_notes() {
  std::string notes;
  { std::lock_guard l(g_m); notes = g_rel.notes; }
  std::string text = core::release_notes_text(notes);
  voice::play_system_sound(voice::CueDecide);
  speech::speak(text.empty() ? std::string(strings::kUpdateNoNotes.c_str()) : text, true);
}
}  // namespace p3a::updater
