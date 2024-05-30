#pragma once
#include <iostream>
#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>

struct XDisplay {
private:
  Display *display = XOpenDisplay(nullptr);

public:
  XDisplay() {
    display = XOpenDisplay(nullptr);
    if (!display)
      throw std::invalid_argument("Could not open display");
  }

  [[nodiscard]] auto KeyDown(const int KeyCode_) const -> bool {
    char keys_return[32];
    XQueryKeymap(display, keys_return);
    const KeyCode kc2 = XKeysymToKeycode(display, KeyCode_);
    const bool buttonDown = !!(keys_return[kc2 >> 3] & (1 << (kc2 & 7)));
    return buttonDown;
  }

  auto MouseClickLeft() const -> void {
    XTestFakeButtonEvent(display, Button1, True, 0);
    XTestFakeButtonEvent(display, Button1, False, 0);
    XFlush(display);
  }

  auto MoveMouse(const int PitchMovement, const int YawMovement) const -> void {
    XTestFakeRelativeMotionEvent(display, YawMovement, PitchMovement, CurrentTime);
    XFlush(display);
  }

  [[nodiscard]] auto Focused() const -> bool {
    Window FocusedWindow;
    int Revert;
    XGetInputFocus(display, &FocusedWindow, &Revert);
    return FocusedWindow == getpid() || FocusedWindow == Memory::GetPID();
  }
};
