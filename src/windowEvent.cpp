#include "windowEvent.hpp"

namespace engine {
  WindowResizedEvent::WindowResizedEvent(int width, int height) 
    : width(width), height(height) {
      eventType = EventType::WindowResized;
  }

  void WindowResizedEvent::publish() {
    std::stringstream ss;
    ss << "WindowResizedEvent: " << width << ", " << height << ".";
    std::cout << ss.str() << std::endl;
  }

  WindowClosedEvent::WindowClosedEvent() {
      eventType = EventType::WindowClosed;
  }

  void WindowClosedEvent::publish() {
    std::cout << "WindowClosedEvent." << std::endl;
  }
}
