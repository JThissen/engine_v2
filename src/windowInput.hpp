#ifndef WINDOW_INPUT_H
#define WINDOW_INPUT_H

#include "headers.hpp"
#include "key.hpp"
#include "mouse.hpp"

namespace engine {
  class WindowInput {
    public:
    static bool isKeyPressed(Key::KeyCode keyCode);
    static bool isMousePressed(Mouse::MouseCode mouseCode);
    static std::pair<float, float> getMousePosition();
  };
}

#endif
