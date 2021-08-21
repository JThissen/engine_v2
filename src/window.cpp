#include "window.hpp"
#include "opengl/openglContext.hpp"
#include "utils.hpp"

namespace engine {
  int Window::windowCount = 0;

  Window::Window(std::string title, std::shared_ptr<EventBus> eventBus, std::optional<int> width, std::optional<int> height)
    : title(title), eventBus(eventBus), width(width.value_or(0)), height(height.value_or(0)) {
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

    GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
	  const GLFWvidmode* videoMode = glfwGetVideoMode(primaryMonitor);
    if(!width || !height) {
      width = videoMode->width;
      height = videoMode->height;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    window = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);

    if(!window) {
      std::cout << "Failed to open window." << std::endl;
      glfwTerminate();
      return;
    }

    openglContext = std::make_unique<OpenglContext>(window);
    openglContext->create();
    glfwSetInputMode(window, GLFW_CURSOR, isCursorEnabled ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
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
    openglContext->swapBuffers();
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

    glfwSetCharCallback(window, [](GLFWwindow* window, unsigned int key) {
      Window* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
      KeyTypedEvent event(key);
      self->eventBus->post(std::bind(&KeyTypedEvent::publish, event));
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
      // self->isMinimized = (width == 0 && height == 0) ? true : false;
      WindowResizedEvent event(width, height);
      self->eventBus->post(std::bind(&WindowResizedEvent::publish, event));
    });

    glfwSetWindowCloseCallback(window, [](GLFWwindow* window) {
      Window* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
      WindowClosedEvent event = WindowClosedEvent();
      self->eventBus->post(std::bind(&WindowClosedEvent::publish, event));
    });

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
      Window* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
      FramebufferResizedEvent event = FramebufferResizedEvent(width, height);
      self->eventBus->post(std::bind(&FramebufferResizedEvent::publish, event));
      glViewport(0, 0, width, height);
    });
  }
}
 