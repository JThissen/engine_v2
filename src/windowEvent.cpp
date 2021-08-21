#include "windowEvent.hpp"
#include "app.hpp"

namespace engine {
  WindowResizedEvent::WindowResizedEvent(int width, int height) 
    : width(width), height(height) {
      eventType = EventType::WindowResized;
  }

  void WindowResizedEvent::publish() {
    std::stringstream ss;
    ss << "WindowResizedEvent: " << width << ", " << height << ".";
    std::cout << ss.str() << std::endl;
    App& app = App::get();
    app.event(*this);
  }

  WindowClosedEvent::WindowClosedEvent() {
      eventType = EventType::WindowClosed;
  }

  void WindowClosedEvent::publish() {
    std::cout << "WindowClosedEvent." << std::endl;
  }

  FramebufferResizedEvent::FramebufferResizedEvent(int width, int height) 
    : width(width), height(height) {
      eventType = EventType::FramebufferResized;
  }

  void FramebufferResizedEvent::publish() {
    std::stringstream ss;
    ss << "FramebufferResizedEvent: " << width << ", " << height << ".";
    std::cout << ss.str() << std::endl;
    App& app = App::get();
    app.event(*this);
  }
}
