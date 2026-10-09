# Santa Claus in Trouble — iOS port scaffold

This repository is an **incomplete native-port scaffold**, not a playable game yet. It preserves the supplied original `xmas.xpk`, `config.txt`, `score.dat`, and `music/m02B.wav` data. It does not include the original Windows executable in the iOS target.

## Language / rendering plan
- C++17: archive/config/level parsing and eventual gameplay systems.
- Objective-C++ (`.mm`): UIKit app lifecycle and bridge to C++.
- Metal / MetalKit: intended iOS renderer.

## Current verified scope
- XPK archive reader opens the supplied package.
- Conservative level record parser accepts the supplied sample levels; its 60-byte record interpretation is **not fully reverse-engineered**.
- iOS screen currently clears a Metal drawable and reports package status only.
- DirectX `.x` mesh decoding, `.ani` animation, textures, real level rendering, player/enemy behavior, collision, HUD, sound effects, and controller input are not implemented.

## Build
The iOS project is generated with XcodeGen from `project.yml`. On a Mac with Xcode and XcodeGen installed:

```sh
brew install xcodegen
xcodegen generate
xcodebuild -project SantaEngine.xcodeproj -scheme SantaEngine -configuration Release -sdk iphoneos -derivedDataPath build CODE_SIGNING_ALLOWED=NO
```

GitHub Actions can compile an **unsigned** app package. An unsigned IPA is not directly installable on a normal iPhone; device installation requires appropriate signing/provisioning.

## Original assets
The source game data is copyrighted. Use only game files you are authorized to use. No new modes, touch controls, or gameplay redesign are intended. The desired iOS controls are a supported external game controller or keyboard.
