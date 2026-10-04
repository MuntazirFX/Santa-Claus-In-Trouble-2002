cmake_minimum_required(VERSION 3.20)
project(SantaEngine CXX)
set(CMAKE_CXX_STANDARD 17)

# Windows (reference/testing build). iOS ko platform/ios/project.yml (XcodeGen) build karta hai.
#   cmake -S . -B build -A Win32
# DirectX SDK (June 2010) chahiye (d3d8.h ke liye); installer DXSDK_DIR set karta hai.
set(DXSDK_DIR "$ENV{DXSDK_DIR}" CACHE PATH "DirectX SDK June 2010 path")

add_executable(SantaEngine WIN32 platform/win32/main.cpp src/core/xpk.cpp src/core/config.cpp src/game/level.cpp)
target_include_directories(SantaEngine PRIVATE "${DXSDK_DIR}/Include" src)
target_link_directories(SantaEngine PRIVATE "${DXSDK_DIR}/Lib/x86")
target_link_libraries(SantaEngine PRIVATE d3d8 d3dx8 dinput8 dsound dxguid ws2_32)
