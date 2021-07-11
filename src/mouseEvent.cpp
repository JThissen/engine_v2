#include "mouseEvent.hpp"

namespace engine {
  MousePressedEvent::MousePressedEvent(int button) 
    : button(button) {
      eventType = EventType::MousePressed;
  }

  void MousePressedEvent::publish() {
    std::stringstream ss;
    ss << "MousePressedEvent: " << button << ".";
    std::cout << ss.str() << std::endl;
  }

  MouseReleasedEvent::MouseReleasedEvent(int button) 
    : button(button) {
      eventType = EventType::MouseReleased;
  }

  void MouseReleasedEvent::publish() {
    std::stringstream ss;
    ss << "MouseReleasedEvent: " << button << ".";
    std::cout << ss.str() << std::endl;
  }

  MouseScrolledEvent::MouseScrolledEvent(int xOffset, int yOffset) 
    : xOffset(xOffset), yOffset(yOffset) {
      eventType = EventType::MouseScrolled;
  }

  void MouseScrolledEvent::publish() {
    std::stringstream ss;
    ss << "MouseScrolledEvent: " << xOffset << ", " << yOffset << ".";
    std::cout << ss.str() << std::endl;
  }

  MousePositionEvent::MousePositionEvent(int x, int y) 
    : x(x), y(y) {
      eventType = EventType::MousePosition;
  }

  void MousePositionEvent::publish() {
    std::stringstream ss;
    ss << "MousePositionEvent: " << x << ", " << y << ".";
    std::cout << ss.str() << std::endl;
  }
}
