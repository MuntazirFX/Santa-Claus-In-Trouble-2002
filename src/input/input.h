#pragma once
// Abstract controls: move X/Z, jump. Keyboard/pad on Windows and supported external controller/keyboard on iOS; no touch controls.
struct InputState { float moveX = 0, moveZ = 0; bool jump = false; };
