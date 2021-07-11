#include "keyEvent.hpp"

namespace engine {
  KeyPressedEvent::KeyPressedEvent(int key, bool isRepeated) 
    : key(key), isRepeated(isRepeated) {
      eventType = EventType::KeyPressed;
  }

  void KeyPressedEvent::publish() {
    std::stringstream ss;
    ss << "KeyPressedEvent: " << key << ". Key repeated: " << std::boolalpha << isRepeated << ".";
    std::cout << ss.str() << std::endl;
  }

  KeyReleasedEvent::KeyReleasedEvent(int key) 
    : key(key), isRepeated(isRepeated) {
      eventType = EventType::KeyReleased;
  }

  void KeyReleasedEvent::publish() {
    std::stringstream ss;
    ss << "KeyReleasedEvent: " << key << ".";
    std::cout << ss.str() << std::endl;
  }
}
