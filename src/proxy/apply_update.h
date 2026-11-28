#pragma once
// Installs an update the mod downloaded (src/updater.cpp), at game start, before the mod is loaded: nothing of the mod's
// is in use yet, so its files can be replaced. Run by the dsound proxy for a Steam launch (never for P3A_DLL).
//
// The updater leaves, in <Win64>\Arcana\update\:
//   new\      the release zip unpacked (dsound.dll, README.txt, INSTALL.txt, Arcana\...)
//   ready     the version it holds ("0.9.0"), written last, once new\ is whole
// This moves each top-level item of new\Arcana into Arcana (the one there first to update\old\Arcana), then the files
// beside it into Win64 (the old ones to update\old). The running dsound.dll (this proxy) can be renamed though loaded:
// the new one runs from the next launch. Any failed move puts back every move made before it. The outcome goes to
// update\result ("installed 0.9.0", "failed ..."), which the mod reads and logs; old\ is removed at the next start
// (the old dsound.dll cannot be deleted while it is loaded).
// A staged version no newer than the one installed (Arcana\version.txt, written by tools/package.py) is dropped: a
// newer zip installed by hand is never replaced by an older download.
#include <windows.h>

#include <string>
#include <vector>

#include "core/version.h"

namespace p3a::update_apply {
inline bool exists(const std::wstring& p) { return GetFileAttributesW(p.c_str()) != INVALID_FILE_ATTRIBUTES; }

inline std::string read_small(const std::wstring& p) {
  HANDLE h = CreateFileW(p.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 0, nullptr);
  if (h == INVALID_HANDLE_VALUE) return {};
  char buf[64] = {};
  DWORD n = 0;
  ReadFile(h, buf, sizeof buf - 1, &n, nullptr);
  CloseHandle(h);
  return std::string(buf, n);
}

inline void write_small(const std::wstring& p, const std::string& text) {
  HANDLE h = CreateFileW(p.c_str(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, 0, nullptr);
  if (h == INVALID_HANDLE_VALUE) return;
  DWORD n = 0;
  WriteFile(h, text.data(), (DWORD)text.size(), &n, nullptr);
  CloseHandle(h);
}

// Deletes a folder and everything in it, as far as it can (a loaded DLL inside stays).
inline void remove_tree(const std::wstring& dir) {
  WIN32_FIND_DATAW fd;
  HANDLE f = FindFirstFileW((dir + L"\\*").c_str(), &fd);
  if (f != INVALID_HANDLE_VALUE) {
    do {
      std::wstring name = fd.cFileName;
      if (name == L"." || name == L"..") continue;
      std::wstring p = dir + L"\\" + name;
      if ((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && !(fd.dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT)) remove_tree(p);
      else {
        if (fd.dwFileAttributes & FILE_ATTRIBUTE_READONLY) SetFileAttributesW(p.c_str(), FILE_ATTRIBUTE_NORMAL);
        DeleteFileW(p.c_str());
      }
    } while (FindNextFileW(f, &fd));
    FindClose(f);
  }
  RemoveDirectoryW(dir.c_str());
}

inline std::vector<std::wstring> list(const std::wstring& dir) {
  std::vector<std::wstring> out;
  WIN32_FIND_DATAW fd;
  HANDLE f = FindFirstFileW((dir + L"\\*").c_str(), &fd);
  if (f == INVALID_HANDLE_VALUE) return out;
  do {
    std::wstring name = fd.cFileName;
    if (name != L"." && name != L"..") out.push_back(name);
  } while (FindNextFileW(f, &fd));
  FindClose(f);
  return out;
}

struct Move { std::wstring from, to; };

// Undoes the moves made so far, newest first.
inline void roll_back(std::vector<Move>& done) {
  for (auto it = done.rbegin(); it != done.rend(); ++it) MoveFileExW(it->to.c_str(), it->from.c_str(), MOVEFILE_REPLACE_EXISTING);
  done.clear();
}

// Puts `name` from `src` into `dst`, the one there first moved to `backup`. False (with the moves made undone by the
// caller) when either move fails.
inline bool replace(const std::wstring& src, const std::wstring& dst, const std::wstring& backup, const std::wstring& name,
                    std::vector<Move>& done) {
  std::wstring target = dst + L"\\" + name;
  if (exists(target)) {
    std::wstring keep = backup + L"\\" + name;
    if (!MoveFileExW(target.c_str(), keep.c_str(), 0)) return false;
    done.push_back({target, keep});
  }
  std::wstring from = src + L"\\" + name;
  if (!MoveFileExW(from.c_str(), target.c_str(), 0)) return false;
  done.push_back({from, target});
  return true;
}

// win64: the game's Binaries\Win64 folder, with no trailing backslash. Returns what it did, for the result file.
inline std::string run(const std::wstring& win64) {
  const std::wstring mod = win64 + L"\\Arcana", up = mod + L"\\update", fresh = up + L"\\new", old = up + L"\\old";
  if (exists(old)) remove_tree(old);   // the last update's leftovers
  const std::wstring ready = up + L"\\ready";
  if (!exists(ready)) return {};
  std::string staged = read_small(ready);
  while (!staged.empty() && (staged.back() == '\n' || staged.back() == '\r' || staged.back() == ' ')) staged.pop_back();
  std::string outcome;
  core::Version sv = core::parse_version(staged.c_str());
  core::Version iv = core::parse_version(read_small(mod + L"\\version.txt").c_str());
  if (!sv.ok || !exists(fresh + L"\\Arcana\\arcana.dll") || !exists(fresh + L"\\dsound.dll")) {
    outcome = "failed: the staged update is incomplete";
  } else if (iv.ok && !core::newer(sv, iv)) {
    outcome = "skipped " + staged + ": not newer than the installed version";
  } else {
    CreateDirectoryW(old.c_str(), nullptr);
    CreateDirectoryW((old + L"\\Arcana").c_str(), nullptr);
    std::vector<Move> done;
    bool ok = true;
    for (const auto& name : list(fresh + L"\\Arcana"))
      if (!(ok = replace(fresh + L"\\Arcana", mod, old + L"\\Arcana", name, done))) break;
    if (ok)
      for (const auto& name : list(fresh))
        if (name != L"Arcana" && !(ok = replace(fresh, win64, old, name, done))) break;
    if (ok) outcome = "installed " + staged;
    else {
      DWORD err = GetLastError();
      roll_back(done);
      outcome = "failed: a file could not be replaced (error " + std::to_string(err) + ")";
    }
  }
  DeleteFileW(ready.c_str());
  remove_tree(fresh);
  for (const auto& name : list(up))   // the downloaded zip
    if (name.size() > 4 && name.substr(name.size() - 4) == L".zip") DeleteFileW((up + L"\\" + name).c_str());
  write_small(up + L"\\result", outcome + "\n");
  return outcome;
}
}  // namespace p3a::update_apply
