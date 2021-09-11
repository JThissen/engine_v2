#ifndef APP_H
#define APP_H

#include "headers.hpp"
#include "window.hpp"
#include "eventBus.hpp"
#include "layers.hpp"
#include "imGuiLayer.hpp"
#include "renderer/shaderBuilder.hpp"
#include "renderer/orthographicCamera.hpp"
#include "opengl/openglVertexArray.hpp"
#include "opengl/openglRenderer.hpp"

namespace engine {
  class App {
    private:
      bool useImGui = false;
      float time = 0.0f;
      float timePreviousFrame = 0.0f;
      DeltaTime deltaTime;
      static App* instance;

    public:
      bool isRunning = true;
      std::unique_ptr<Window> window;
      std::shared_ptr<EventBus> eventBus;
      std::shared_ptr<ImGuiLayer> imGuiLayer;
      Layers layers;
      
      App(bool useImGui);
      virtual ~App() = default;
      void run();
      void updateTime();
      void updateLayers();
      void updateImGui();
      void close();
      void resize(const WindowResizedEvent& event);
      void event(Event& event);
      static App& get();
  };
}

#endif
