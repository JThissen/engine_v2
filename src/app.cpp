#include "app.hpp"
#include "windowInput.hpp"
#include "imGuiLayer.hpp"
#include "renderer/layoutBuffer.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

namespace engine {
  App* App::instance = nullptr;
  
  App& App::get() { 
    return *instance; 
  }

  App::App(bool useImGui) : useImGui(useImGui) {
    if(instance != nullptr) {
      std::cout << "Only 1 instance of App may be created." << std::endl;
    } 
    instance = this;
    eventBus = std::make_shared<EventBus>();
    eventBus->start();
    window = std::make_unique<Window>("engine", 800, 600, eventBus);

    if(useImGui) {
      imGuiLayer = std::make_unique<ImGuiLayer>();
      layers.pushLayer(imGuiLayer);
    }
  }

  void App::run() {
    while(isRunning) {
      time = static_cast<float>(glfwGetTime());
      deltaTime = DeltaTime(time - timePreviousFrame);
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
    isRunning = false;
  }

  void App::resize(const WindowResizedEvent& event) {
    // t.b.d.
  }

  void App::event(Event& event) {
    for(const auto& layer : layers.layers) {
      layer->event(event);
    }
  }
}
