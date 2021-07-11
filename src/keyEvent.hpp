#ifndef KEY_EVENT_H
#define KEY_EVENT_H

#include "headers.hpp"
#include "event.hpp"
#include "windows.h"

namespace engine {
  class KeyPressedEvent : public Event {
    public:
    int key;
    bool isRepeated;
  
    KeyPressedEvent(int key, bool isRepeated = false);
    void publish();
  };

  class KeyReleasedEvent : public Event {
    public:
    int key;
    bool isRepeated;
  
    KeyReleasedEvent(int key);
    void publish();
  };
}

#endif
