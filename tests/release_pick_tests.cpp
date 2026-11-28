#include "doctest.h"
#include <string>
#include "core/release_pick.h"
#include "core/version.h"

using namespace p3a::core;

TEST_CASE("version: release numbers and tags are read, anything else refused") {
  Version v = parse_version("0.8.0");
  CHECK(v.ok);
  CHECK(v.part[0] == 0);
  CHECK(v.part[1] == 8);
  CHECK(v.part[2] == 0);
  CHECK(parse_version("v1.12.3").ok);
  CHECK(parse_version("0.8.0\r\n").ok);   // a line from a file
  CHECK_FALSE(parse_version("0.8").ok);
  CHECK_FALSE(parse_version("0.8.0-rc1").ok);
  CHECK_FALSE(parse_version("0.8.0.1").ok);
  CHECK_FALSE(parse_version("").ok);
  CHECK_FALSE(parse_version(nullptr).ok);
  CHECK_FALSE(parse_version("test").ok);
}

TEST_CASE("version: compared part by part, as numbers") {
  CHECK(newer(parse_version("0.10.0"), parse_version("0.9.9")));
  CHECK(newer(parse_version("1.0.0"), parse_version("0.99.99")));
  CHECK(newer(parse_version("0.8.1"), parse_version("0.8.0")));
  CHECK_FALSE(newer(parse_version("0.8.0"), parse_version("0.8.0")));
  CHECK_FALSE(newer(parse_version("0.7.9"), parse_version("0.8.0")));
}

static const char* kDigest = "9f47e8d4e0c22ca9039b05ec3ad61e1ec1df54cb71fe699c451f0c37210c370b";

static std::string release(const char* tag, const char* zip, bool draft = false, const char* digest = kDigest) {
  return std::string("{\"tag_name\":\"") + tag + "\",\"draft\":" + (draft ? "true" : "false") +
         ",\"prerelease\":true,\"body\":\"## What's new\\n- One \\u00e9\",\"assets\":[{\"name\":\"" + zip +
         "\",\"size\":158738196,\"digest\":\"sha256:" + digest +
         "\",\"browser_download_url\":\"https://github.com/o/r/releases/download/" + tag + "/" + zip + "\"}]}";
}

TEST_CASE("release_pick: the newest later release with its zip is offered") {
  std::string json = "[" + release("v0.9.0", "arcana-0.9.0.zip") + "," + release("v0.10.0", "arcana-0.10.0.zip") + "," +
                     release("v0.7.0", "arcana-0.7.0.zip") + "]";
  auto r = pick_release(json, parse_version("0.8.0"));
  REQUIRE(r);
  CHECK(r->version == "0.10.0");
  CHECK(r->zip_url == "https://github.com/o/r/releases/download/v0.10.0/arcana-0.10.0.zip");
  CHECK(r->sha256 == kDigest);
  CHECK(r->size == 158738196ull);
  CHECK(r->notes == "## What's new\n- One \xC3\xA9");
}

TEST_CASE("release_pick: nothing newer, drafts, test tags and releases without a checked zip are passed over") {
  CHECK_FALSE(pick_release("[" + release("v0.8.0", "arcana-0.8.0.zip") + "]", parse_version("0.8.0")));
  CHECK_FALSE(pick_release("[" + release("v0.9.0", "arcana-0.9.0.zip", true) + "]", parse_version("0.8.0")));
  CHECK_FALSE(pick_release("[" + release("v0.9.0-test", "arcana-0.9.0.zip") + "]", parse_version("0.8.0")));
  CHECK_FALSE(pick_release("[" + release("v0.9.0", "arcana-0.8.0.zip") + "]", parse_version("0.8.0")));
  CHECK_FALSE(pick_release("[" + release("v0.9.0", "arcana-0.9.0.zip", false, "abc") + "]", parse_version("0.8.0")));
  CHECK_FALSE(pick_release("{\"message\":\"API rate limit exceeded\"}", parse_version("0.8.0")));
  CHECK_FALSE(pick_release("[{\"tag_name\":", parse_version("0.8.0")));
  CHECK_FALSE(pick_release("", parse_version("0.8.0")));
  // a broken newest release does not hide a good older one
  auto r = pick_release("[" + release("v0.10.0", "wrong.zip") + "," + release("v0.9.0", "arcana-0.9.0.zip") + "]", parse_version("0.8.0"));
  REQUIRE(r);
  CHECK(r->version == "0.9.0");
}

TEST_CASE("release_pick: the notes are the What's new section, made plain") {
  const char* body =
      "## What this is\n\nArcana is a mod.\n\n## What's new in this version\n\nThe highlights. See [CHANGELOG.md](https://x/y).\n\n"
      "### Battle\n- Each **hit** is read: `38 damage`.\n- Another\n\n## Install\n\nCopy it.\n";
  CHECK(release_notes_text(body) == "The highlights. See CHANGELOG.md.\nBattle.\nEach hit is read: 38 damage.\nAnother.");
  CHECK(release_notes_text("Just a line") == "Just a line.");
}

TEST_CASE("release_pick: a digest is lowercase hex") {
  unsigned char b[32] = {};
  b[0] = 0xAB;
  b[31] = 0x01;
  std::string h = hex_digest(b);
  CHECK(h.size() == 64);
  CHECK(h.starts_with("ab00"));
  CHECK(h.ends_with("01"));
}
