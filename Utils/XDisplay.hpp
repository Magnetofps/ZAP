#pragma once
#include <iostream>
#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>

struct XDisplay {
private:
  Display *display = XOpenDisplay(nullptr);
  mutable pid_t PID = 0;

  static auto HandleXError(Display* display, XErrorEvent* error_event) -> int {
    return 0; // we just don't wanna crash when getting pid of a window that's terminating
  }

  // when you play the game through valves gamescope you never actually focus the game itself, as it's wrapped into gs
  [[nodiscard]] auto GSPID() const -> pid_t {
    if (PID > 0)
      return PID;

    for (const auto &Entry: std::filesystem::directory_iterator("/proc")) {
      if (!Entry.is_directory())
        continue;

      std::ifstream CommandFile(std::string(Entry.path()) + "/cmdline");
      std::string CommandLine;
      std::getline(CommandFile, CommandLine);

      if (CommandLine.find("gamescope") != std::string::npos) {
        PID = std::stoi(Entry.path().filename());
      }
    }
    return PID;
  }

  static auto GetWindowPID(Display* display, const Window window) -> pid_t { // unfortunately have to do this i think
    const Atom PidAtom = XInternAtom(display, "_NET_WM_PID", True);
    if (PidAtom == None)
      return -1;

    Atom ActualType;
    int ActualFormat;
    unsigned long nItems;
    unsigned long BytesAfter;
    unsigned char* PropID = nullptr;

    if (const int status = XGetWindowProperty(display, window, PidAtom, 0, 1, False, XA_CARDINAL, &ActualType, &ActualFormat, &nItems, &BytesAfter, &PropID);
      status != Success || nItems == 0) {
      return -1;
    }

    const pid_t pid = *reinterpret_cast<pid_t *>(PropID);
    XFree(PropID);
    return pid;
  }

public:
  XDisplay() {
    display = XOpenDisplay(nullptr);
    if (!display)
      throw std::invalid_argument("Could not open display");

    XSetErrorHandler(HandleXError);
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
    const auto FocusedPID = GetWindowPID(display, FocusedWindow);
    return FocusedPID == getpid() || FocusedPID == Memory::GetPID() || FocusedPID == GSPID();;
  }
};
