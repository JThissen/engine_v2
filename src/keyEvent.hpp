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
    std::string keyName;
  
    KeyPressedEvent(int key, bool isRepeated = false);
    void publish();
  };

  class KeyReleasedEvent : public Event {
    public:
    Key::KeyCode keyCode;
    bool isRepeated;
    std::string keyName;
  
    KeyReleasedEvent(int key);
    void publish();
  };

  class KeyTypedEvent : public Event {
    public:
    Key::KeyCode keyCode;
    std::string keyName;
  
    KeyTypedEvent(int key);
    void publish();
  };
}

#endif
