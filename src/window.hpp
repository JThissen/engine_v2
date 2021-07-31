#ifndef WINDOW_H
#define WINDOW_H

#include "headers.hpp"
#include "eventBus.hpp"
#include "keyEvent.hpp"
#include "mouseEvent.hpp"
#include "windowEvent.hpp"
#include "opengl/openglContext.hpp"

namespace engine {
  class Window {
    public:
      std::string title;
      int width;
      int height;
      static int windowCount;
      GLFWwindow* window;
      std::shared_ptr<EventBus> eventBus;
      std::unique_ptr<OpenglContext> openglContext;

      Window(std::string title, int width, int height, std::shared_ptr<EventBus> eventBus);
      ~Window();
      void create();
      void destroy();
      void update();
      void setCallbacks();
  };
}

#endif
