#include "mouseEvent.hpp"
#include "app.hpp"

namespace engine {
  MousePressedEvent::MousePressedEvent(int button) 
    : mouseCode(static_cast<Mouse::MouseCode>(button)) {
      eventType = EventType::MousePressed;
      auto it = Mouse::map.find(static_cast<Mouse::MouseCode>(button));
      buttonName = (it != Mouse::map.end()) ? it->second : "Button undefined";
  }

  void MousePressedEvent::publish() {
    std::stringstream ss;
    ss << "MousePressedEvent: " << buttonName << ".";
    std::cout << ss.str() << std::endl;
    App& app = App::get();
    app.event(*this);
  }

  MouseReleasedEvent::MouseReleasedEvent(int button) 
    : button(static_cast<Mouse::MouseCode>(button)) {
      eventType = EventType::MouseReleased;
      auto it = Mouse::map.find(static_cast<Mouse::MouseCode>(button));
      buttonName = (it != Mouse::map.end()) ? it->second : "Button undefined";
  }

  void MouseReleasedEvent::publish() {
    std::stringstream ss;
    ss << "MouseReleasedEvent: " << buttonName << ".";
    std::cout << ss.str() << std::endl;
    App& app = App::get();
    app.event(*this);
  }

  MouseScrolledEvent::MouseScrolledEvent(int xOffset, int yOffset) 
    : xOffset(xOffset), yOffset(yOffset) {
      eventType = EventType::MouseScrolled;
  }

  void MouseScrolledEvent::publish() {
    std::stringstream ss;
    ss << "MouseScrolledEvent: " << xOffset << ", " << yOffset << ".";
    std::cout << ss.str() << std::endl;
    App& app = App::get();
    app.event(*this);
  }

  MousePositionEvent::MousePositionEvent(int x, int y) 
    : x(x), y(y) {
      eventType = EventType::MousePosition;
  }

  void MousePositionEvent::publish() {
    std::stringstream ss;
    ss << "MousePositionEvent: " << x << ", " << y << ".";
    std::cout << ss.str() << std::endl;
    App& app = App::get();
    app.event(*this);
  }
}
