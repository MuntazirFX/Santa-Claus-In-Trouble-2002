#pragma once
// Abstract controls: move X/Z, jump. Keyboard/pad on Windows, virtual joystick + button on iOS.
struct InputState { float moveX = 0, moveZ = 0; bool jump = false; };
