#pragma once
// The updater's reading of GitHub's release list (src/updater.cpp): which release to offer, and its notes as plain text.
#include <cstdint>
#include <optional>
#include <string>
#include <string_view>

#include "core/version.h"

namespace p3a::core {
struct Release {
  std::string version;   // "0.8.0"
  std::string zip_url;   // the arcana-<version>.zip asset's download address
  std::string sha256;    // its SHA-256 as GitHub computed it on upload, 64 lowercase hex digits
  uint64_t size = 0;     // its size in bytes
  std::string notes;     // the release's body, as written (Markdown)
};

// The newest release later than `current` in the JSON of GET /repos/<owner>/<repo>/releases: not a draft, a tag
// "v<major>.<minor>.<patch>", an asset named "arcana-<version>.zip" with a "sha256:" digest. Pre-releases count (every
// release so far is one). Nothing when none is newer, or the text is not that list.
std::optional<Release> pick_release(std::string_view json, const Version& current);

// The "What's new" section of a release body as lines to read: headings, bullets and links made plain, the other
// sections left out. The whole body made plain when it has no such section.
std::string release_notes_text(std::string_view body);

// Lowercase hex of 32 bytes (a SHA-256).
std::string hex_digest(const unsigned char (&bytes)[32]);
}  // namespace p3a::core
