#include "keyEvent.hpp"

namespace engine {
  KeyPressedEvent::KeyPressedEvent(int key, bool isRepeated) 
    : keyCode(static_cast<Key::KeyCode>(key)), isRepeated(isRepeated) {
      eventType = EventType::KeyPressed;
      auto f = Key::map.find(static_cast<Key::KeyCode>(key));
      this->key = (f != Key::map.end()) ? f->second : "Key undefined";
  }

  void KeyPressedEvent::publish() {
    std::stringstream ss;
    ss << "KeyPressedEvent: " << key << ". Key repeated: " << std::boolalpha << isRepeated << ".";
    std::cout << ss.str() << std::endl;
  }

  KeyReleasedEvent::KeyReleasedEvent(int key) 
    : keyCode(static_cast<Key::KeyCode>(key)), isRepeated(isRepeated) {
      eventType = EventType::KeyReleased;
      auto f = Key::map.find(static_cast<Key::KeyCode>(key));
      this->key = (f != Key::map.end()) ? f->second : "Key undefined";
  }

  void KeyReleasedEvent::publish() {
    std::stringstream ss;
    ss << "KeyReleasedEvent: " << key << ".";
    std::cout << ss.str() << std::endl;
  }
}
