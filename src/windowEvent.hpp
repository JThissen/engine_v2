#ifndef WINDOW_EVENT_H
#define WINDOW_EVENT_H

#include "headers.hpp"
#include "event.hpp"
#include "windows.h"

namespace engine {
  class WindowResizedEvent : public Event {
    public:
    int width;
    int height;
  
    WindowResizedEvent(int width, int height);
    void publish();
  };

  class WindowClosedEvent : public Event {
    public:
    WindowClosedEvent();
    void publish();
  };

  class FramebufferResizedEvent : public Event {
    public:
    int width;
    int height;
  
    FramebufferResizedEvent(int width, int height);
    void publish();
  };
}

#endif
