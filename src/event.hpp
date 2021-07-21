#ifndef EVENT_H
#define EVENT_H

#include "headers.hpp"
#include "windows.h"

namespace engine {
  class Event {
    public:
    enum class EventType {
      WindowClosed,
      WindowResized,
      WindowMoved,
      KeyPressed,
      KeyReleased,
      KeyTyped,
      MousePressed,
      MouseReleased,
      MousePosition,
      MouseScrolled
    };
    static std::unordered_map<EventType, std::string> eventTypeMap;
    EventType eventType;
    std::chrono::system_clock::time_point date = std::chrono::system_clock::now();
    Event();
    virtual ~Event() = default;
    virtual void publish() = 0;

    private:
    HANDLE hConsole;
  };
}

#endif
