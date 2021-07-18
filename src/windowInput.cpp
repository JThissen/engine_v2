#include "windowInput.hpp"
#include "app.hpp"

namespace engine {
  bool WindowInput::isKeyPressed(Key::KeyCode keyCode) {
    GLFWwindow* window = App::get().window->window;
    int key = glfwGetKey(window, static_cast<int>(keyCode));
    return key == GLFW_PRESS || key == GLFW_REPEAT;
  }

  bool WindowInput::isMousePressed(Mouse::MouseCode mouseCode) {
    GLFWwindow* window = App::get().window->window;
    int mouse = glfwGetMouseButton(window, static_cast<int>(mouseCode));
    return mouse == GLFW_PRESS;
  }

  std::pair<float, float> WindowInput::getMousePosition() {
    GLFWwindow* window = App::get().window->window;
    double x;
    double y;
    glfwGetCursorPos(window, &x, &y);
    return std::pair<float, float>(x, y);
  }
}