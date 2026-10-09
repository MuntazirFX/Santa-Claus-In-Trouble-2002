# Santa Claus in Trouble iOS — ZIP audit and fixes

## User goal
Native iOS port of the original 2002 PC game. Preserve original assets, levels, gameplay and visual style. No mods, no gameplay redesign, and no touch controls. Planned iOS controls: supported external controller/keyboard.

## ZIPs compared
- `SantaEngine.zip` (source scaffold)
- `Santa Claus in Trouble(2).zip` (PC game files)

The following original data files in the source ZIP were compared against the PC ZIP and their SHA-256 hashes matched exactly: `xmas.xpk`, `config.txt`, `score.dat`, `music/m02B.wav`. The original Windows executable is not copied into the iOS bundle.

## Fixes applied in this project
1. Removed the reference to a missing custom `platform/ios/Info.plist`; XcodeGen now generates the Info.plist from `project.yml` properties.
2. Hardened XPK parsing: file-seek failures are checked, name strings must terminate within the name block, and archive header/table/data boundaries are checked. Windows and POSIX large-file APIs are handled separately.
3. Corrected the test tool so it loads `config.txt` before printing the resulting values.
4. Updated the input abstraction comment to explicitly exclude touch controls.
5. Added a parser validation step to GitHub Actions and documented the current implementation honestly.

## Validation performed here
- Compiled the C++ data test using Clang C++17 with `-Wall -Wextra -Wpedantic`: passed.
- Opened the supplied `xmas.xpk`: passed.
- Parsed sample levels `000`–`010`, `100`, and `demo`: all passed the current 60-byte record-size check.
- Original-data hashes listed above match.

## Important limitations / not yet fixed
This is **not a complete or playable port**. No Mac/Xcode/iOS SDK was available in this audit environment, so XcodeGen and the iOS target were not built here. The Metal renderer currently clears the screen only. DirectX `.x` model parsing, `.ani` animation, textures, original level rendering, player/enemy logic, collision/physics, original HUD/menu, SFX/music integration, and external controller/keyboard gameplay input remain unimplemented. The `.dat` 60-byte layout is a conservative hypothesis validated only by record lengths and sample parsing, not a fully verified proprietary-format specification.

## Next engineering milestones
1. Generate/build the Xcode project on macOS and fix any SDK/compiler issues.
2. Inventory XPK entries and reverse-engineer the actual `.x`/`.ani`/texture formats.
3. Implement and test a real Metal mesh/texture pipeline, then load one original level without replacing assets.
4. Implement original player movement, camera, collision, collectibles, hazards, checkpoints, enemies, scoring, menus and audio against observed PC behavior.
5. Add external controller/keyboard input only; do not add on-screen touch controls.
6. Compare levels and gameplay against the PC release before calling the port faithful.

## Signing note
The GitHub workflow is intended to produce an **unsigned** IPA artifact. Installing on a physical iPhone normally requires signing/provisioning; successful packaging is not proof of playability.
