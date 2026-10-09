name: iOS Build (unsigned IPA)
on:
  push:
  workflow_dispatch:

jobs:
  build:
    runs-on: macos-latest
    steps:
      - uses: actions/checkout@v4

      - name: Install XcodeGen
        run: brew install xcodegen

      - name: Generate Xcode project
        run: xcodegen generate

      - name: Build (no signing)
        run: |
          xcodebuild -project SantaEngine.xcodeproj -scheme SantaEngine \
            -configuration Release -sdk iphoneos -derivedDataPath build \
            CODE_SIGNING_ALLOWED=NO CODE_SIGNING_REQUIRED=NO CODE_SIGN_IDENTITY=""

      - name: Package IPA
        run: |
          mkdir Payload
          cp -R build/Build/Products/Release-iphoneos/SantaEngine.app Payload/
          zip -qr SantaEngine.ipa Payload

      - uses: actions/upload-artifact@v4
        with:
          name: SantaEngine-ipa
          path: SantaEngine.ipa
