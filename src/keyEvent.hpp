#ifndef KEY_EVENT_H
#define KEY_EVENT_H

#include "headers.hpp"
#include "event.hpp"
#include "key.hpp"
#include "windows.h"

namespace engine {
  class KeyPressedEvent : public Event {
    public:
    Key::KeyCode keyCode;
    bool isRepeated;
    std::string key;
  
    KeyPressedEvent(int key, bool isRepeated = false);
    void publish();
  };

  class KeyReleasedEvent : public Event {
    public:
    Key::KeyCode keyCode;
    bool isRepeated;
    std::string key;
  
    KeyReleasedEvent(int key);
    void publish();
  };
}

#endif
