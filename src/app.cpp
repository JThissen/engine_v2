#include "app.hpp"
#include "windowInput.hpp"

namespace engine {
  App* App::instance = nullptr;
  
  App& App::get() { 
    return *instance; 
  }

  App::App() {
    if(instance != nullptr) {
      std::cout << "Only 1 instance of App may be created." << std::endl;
    } 
    instance = this;
    eventBus = std::make_shared<EventBus>();
    eventBus->start();
    window = std::make_unique<Window>("engine", 800, 600, eventBus);
  }

  void App::run() {
    while(running) {
      float time = static_cast<float>(glfwGetTime());
      DeltaTime deltaTime = DeltaTime(time - timePreviousFrame);
      timePreviousFrame = time;

      for(const auto& layer : layers.layers) {
        layer->update(deltaTime);
      }

      for(const auto& layer : layers.overlays) {
        layer->update(deltaTime);
      }

      window->update();
    }
  }

  void App::close() {
    running = false;
  }

  void App::resize(const WindowResizedEvent& event) {
    // t.b.d.
  }

  void App::event(Event& event) {
    for(const auto& layer : layers.layers) {
      layer->event(event);
    }
  }

  void App::pushLayer(std::unique_ptr<Layer>& layer) {
    layer->push();
    layers.pushLayer(layer);
  }
}
