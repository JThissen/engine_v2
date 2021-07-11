#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "headers.hpp"
#include "eventBus.hpp"
#include "keyEvent.hpp"
#include "mouseEvent.hpp"
#include "windowEvent.hpp"

namespace engine {
  class Window {
    public:
      std::string title;
      int width;
      int height;
      static int windowCount;
      GLFWwindow* window;
      std::shared_ptr<EventBus> eventBus;

      Window(std::string title, int width, int height, std::shared_ptr<EventBus> eventBus);
      ~Window();
      void create();
      void destroy();
      void update();
      void setCallbacks();
  };
}

#endif
