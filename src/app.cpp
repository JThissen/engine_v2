#include "app.hpp"
#include "windowInput.hpp"
#include "renderer/layoutBuffer.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include "utils.hpp"

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
    window = std::make_unique<Window>("engine", eventBus, 1600, 900);

    if(useImGui) {
      imGuiLayer = std::make_shared<ImGuiLayer>();
      layers.pushLayer(imGuiLayer);
    }
  }

  void App::run() {
    while(isRunning) {
      updateTime();
      updateLayers();
      updateImGui();
      window->update();
    }
  }

  void App::updateTime() {
    time = static_cast<float>(glfwGetTime());
    deltaTime = DeltaTime(time - timePreviousFrame);
    timePreviousFrame = time;
  }

  void App::updateLayers() {
    for(const auto& layer : layers.layers) {
        layer->update(time, deltaTime);
    }

    for(const auto& layer : layers.overlays) {
      layer->update(time, deltaTime);
    }
  }

  void App::updateImGui() {
    imGuiLayer->newFrame();
      for(const auto& layer : layers.layers) {
        layer->createImGuiLayout();
      }
      imGuiLayer->render();
  }

  void App::close() {
    isRunning = false;
  }

  void App::event(Event& event) {
    if(event.eventType == Event::EventType::KeyPressed) {
      try {
        auto keyPressedEvent = dynamic_cast<KeyPressedEvent&>(event);
        if(keyPressedEvent.keyName == Key::map[Key::KeyCode::Escape]) {
          isRunning = false;
        }
      } catch(const std::bad_cast& error) {
        Utils::print(error.what());
      }
    }

    for(const auto& layer : layers.layers) {
      layer->event(event);
    }
  }
}
