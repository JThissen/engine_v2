#include "event.hpp"

namespace engine {
  std::unordered_map<Event::EventType, std::string> Event::eventTypeMap = {
    { Event::EventType::WindowClosed , "WindowClosed" },
    { Event::EventType::WindowResized, "WindowResized" },
    { Event::EventType::WindowMoved  , "WindowMoved" },
    { Event::EventType::KeyPressed   , "KeyPressed" },
    { Event::EventType::KeyReleased  , "KeyReleased" },
    { Event::EventType::MousePressed , "MousePressed" },
    { Event::EventType::MouseReleased, "MouseReleased" },
    { Event::EventType::MousePosition, "MousePosition" },
    { Event::EventType::MouseScrolled, "MouseScrolled" },
    { Event::EventType::FramebufferResized, "FramebufferResized" }
  };

  Event::Event() {
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
  }
}