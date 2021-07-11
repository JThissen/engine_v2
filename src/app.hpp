#ifndef APP_H
#define APP_H

#include "headers.hpp"
#include "window.hpp"
#include "deltatime.hpp"
#include "eventBus.hpp"

namespace engine {
  class App {
    private:
      bool running = true;
      float timePreviousFrame = 0.0f;
    
    public:
      std::unique_ptr<Window> window;
      std::shared_ptr<EventBus> eventBus;
      App();
      void run();
      void close();
      void resize();
  };
}

#endif
