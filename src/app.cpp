#include "app.hpp"

namespace engine {
  App::App() {
    eventBus = std::make_shared<EventBus>();
    eventBus->start();
    window = std::make_unique<Window>("engine", 800, 600, eventBus);
  }

  void App::run() {
    while(running) {
      float time = static_cast<float>(glfwGetTime());
      DeltaTime deltaTime = time - timePreviousFrame;
      timePreviousFrame = time;
      window->update();
    }
  }

  void App::close() {
    running = false;
  }

  void App::resize() {

  }
}
