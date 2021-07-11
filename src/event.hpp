#ifndef EVENT_H
#define EVENT_H

#include "headers.hpp"
#include "windows.h"

namespace engine {
  enum class EventType {
    WindowClosed,
    WindowResized,
    WindowMoved,
    KeyPressed,
    KeyReleased,
    MousePressed,
    MouseReleased,
    MousePosition,
    MouseScrolled
  };

  class Event {
    public:
    EventType eventType;
    std::chrono::system_clock::time_point date = std::chrono::system_clock::now();

    Event() {
      hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
      SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    }
    virtual ~Event() = default;
    virtual void publish() = 0;

    private:
    HANDLE hConsole;
  };
}

#endif
