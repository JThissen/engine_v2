#include "keyEvent.hpp"
#include "app.hpp"

namespace engine {
  KeyPressedEvent::KeyPressedEvent(int key, bool isRepeated) 
    : keyCode(static_cast<Key::KeyCode>(key)), isRepeated(isRepeated) {
      eventType = EventType::KeyPressed;
      auto f = Key::map.find(static_cast<Key::KeyCode>(key));
      keyName = (f != Key::map.end()) ? f->second : "Key undefined";
  }

  void KeyPressedEvent::publish() {
    std::stringstream ss;
    ss << "KeyPressedEvent: " << keyName << ". Key repeated: " << std::boolalpha << isRepeated << ".";
    std::cout << ss.str() << std::endl;
    App& app = App::get();
    app.event(*this);
  }

  KeyReleasedEvent::KeyReleasedEvent(int key) 
    : keyCode(static_cast<Key::KeyCode>(key)), isRepeated(isRepeated) {
      eventType = EventType::KeyReleased;
      auto f = Key::map.find(static_cast<Key::KeyCode>(key));
      keyName = (f != Key::map.end()) ? f->second : "Key undefined";
  }

  void KeyReleasedEvent::publish() {
    std::stringstream ss;
    ss << "KeyReleasedEvent: " << keyName << ".";
    std::cout << ss.str() << std::endl;
    App& app = App::get();
    app.event(*this);
  }

  KeyTypedEvent::KeyTypedEvent(int key) 
    : keyCode(static_cast<Key::KeyCode>(key)) {
      eventType = EventType::KeyTyped;
      auto f = Key::map.find(static_cast<Key::KeyCode>(key));
      keyName = (f != Key::map.end()) ? f->second : "Key undefined";
  }

  void KeyTypedEvent::publish() {
    std::stringstream ss;
    ss << "KeyTypedEvent: " << keyName;
    std::cout << ss.str() << std::endl;
    App& app = App::get();
    app.event(*this);
  }
}
