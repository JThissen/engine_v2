#ifndef MOUSE_EVENT_H
#define MOUSE_EVENT_H

#include "headers.hpp"
#include "event.hpp"
#include "windows.h"
#include "mouse.hpp"

namespace engine {
  class MousePressedEvent : public Event {
    public:
    Mouse::MouseCode mouseCode;
    std::string buttonName;
  
    MousePressedEvent(int button);
    void publish();
  };

  class MouseReleasedEvent : public Event {
    public:
    Mouse::MouseCode button;
    std::string buttonName;
  
    MouseReleasedEvent(int button);
    void publish();
  };

  class MouseScrolledEvent : public Event {
    public:
    int xOffset;
    int yOffset;
  
    MouseScrolledEvent(int xOffset, int yOffset);
    void publish();
  };

  class MousePositionEvent : public Event {
    public:
    int x;
    int y;
  
    MousePositionEvent(int x, int y);
    void publish();
  };
}

#endif
