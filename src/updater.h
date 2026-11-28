#pragma once
#include <string>

// The updater: asks GitHub for a newer release, downloads and checks it, and unpacks it beside the mod for the dsound
// proxy to install at the next start (src/proxy/apply_update.h). Only a release build checks: tools/package.py builds
// the version in (P3A_VERSION); a dev build has none. The settings menu's Updates category drives it.
namespace p3a::updater {
void install();    // reads what the proxy did at this start, starts the startup check (Check at startup on)
void shutdown();   // waits for the worker before the DLL unloads (dev hot reload)
void tick();       // says what the worker found, on the game thread

// The Updates rows of the settings menu
std::string status_line();   // where the updater stands, and what Enter does
void activate();             // Enter on that row: check, download, or say where it stands
bool has_notes();            // a newer release is known
std::string notes_title();   // "What's new in 0.9.0"
void read_notes();
}  // namespace p3a::updater
