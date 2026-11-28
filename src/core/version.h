#pragma once
// Release versions ("0.8.0", "v0.8.0"): parsed and compared. Header-only and free of the standard library's
// containers, so the dsound proxy (src/proxy) shares it with the updater (src/updater.cpp).

namespace p3a::core {
struct Version {
  int part[3] = {0, 0, 0};
  bool ok = false;   // three numbers were read
};

// "0.8.0" or "v0.8.0" (a tag); a fourth part or anything after the third number ("0.8.0-rc1") is refused, so a
// test tag is never taken for a release.
inline Version parse_version(const char* s) {
  Version v;
  if (!s) return v;
  if (*s == 'v' || *s == 'V') ++s;
  for (int i = 0; i < 3; ++i) {
    if (*s < '0' || *s > '9') return v;
    int n = 0;
    while (*s >= '0' && *s <= '9') {
      n = n * 10 + (*s - '0');
      if (n > 99999) return v;
      ++s;
    }
    v.part[i] = n;
    if (i < 2) {
      if (*s != '.') return v;
      ++s;
    }
  }
  // a line read from a file may end in blanks or a line break
  while (*s == ' ' || *s == '\t' || *s == '\r' || *s == '\n') ++s;
  if (*s) return v;
  v.ok = true;
  return v;
}

// a later than b (both valid)
inline bool newer(const Version& a, const Version& b) {
  for (int i = 0; i < 3; ++i)
    if (a.part[i] != b.part[i]) return a.part[i] > b.part[i];
  return false;
}
}  // namespace p3a::core
