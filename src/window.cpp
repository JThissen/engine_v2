#include "window.hpp"

namespace engine {
  int Window::windowCount = 0;

  Window::Window(std::string title, int width, int height, std::shared_ptr<EventBus> eventBus)
    : title(title), width(width), height(height), eventBus(eventBus) {
    create();
  }

  Window::~Window() {
    destroy();
  }

  void Window::create() {
    if(windowCount == 0) {
      int initialization = glfwInit();

      if(!initialization) {
        std::cout << "Unable to initialize GLFW." << std::endl;
        return;
      }
    }
    window = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);

    if(!window) {
      std::cout << "Failed to open window." << std::endl;
      glfwTerminate();
      return;
    }

    glfwSwapInterval(1);
    setCallbacks();
  }

  void Window::destroy() {
    glfwDestroyWindow(window);
    windowCount--;
    glfwTerminate();
  }

  void Window::update() {
    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  void Window::setCallbacks() {
    glfwSetWindowUserPointer(window, static_cast<void*>(this));

    glfwSetErrorCallback([](int error, const char* description) {
      std::cout << "Error: " << error << "\nDescription: " << description << std::endl;
    });

    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
      Window* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
      switch(action) {
        case GLFW_PRESS: {
          KeyPressedEvent event(key);
          self->eventBus->post(std::bind(&KeyPressedEvent::publish, event));
          break;
        }
        case GLFW_RELEASE: {
          KeyReleasedEvent event(key);
          self->eventBus->post(std::bind(&KeyReleasedEvent::publish, event));
          break;
        }
        case GLFW_REPEAT: {
          KeyPressedEvent event(key, true);
          self->eventBus->post(std::bind(&KeyPressedEvent::publish, event));
          break;
        }
      }
    });

    glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
      Window* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
      switch(action) {
        case GLFW_PRESS: {
          MousePressedEvent event(button);
          self->eventBus->post(std::bind(&MousePressedEvent::publish, event));
          break;
        }
        case GLFW_RELEASE: {
          MouseReleasedEvent event(button);
          self->eventBus->post(std::bind(&MouseReleasedEvent::publish, event));               
          break;
        }
      }
    });

    glfwSetScrollCallback(window, [](GLFWwindow* window, double xOffset, double yOffset) {
      Window* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
      MouseScrolledEvent event(xOffset, yOffset);
      self->eventBus->post(std::bind(&MouseScrolledEvent::publish, event));
    });

    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double x, double y) {
      Window* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
      MousePositionEvent event(x, y);
      self->eventBus->post(std::bind(&MousePositionEvent::publish, event));
    });

    glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {
      Window* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
      WindowResizedEvent event(width, height);
      self->eventBus->post(std::bind(&WindowResizedEvent::publish, event));
    });

    glfwSetWindowCloseCallback(window, [](GLFWwindow* window) {
      Window* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
      WindowClosedEvent event = WindowClosedEvent();
      self->eventBus->post(std::bind(&WindowClosedEvent::publish, event));
    });
  }
}
 