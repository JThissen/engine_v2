#ifndef APP_H
#define APP_H

#include "headers.hpp"
#include "window.hpp"
#include "eventBus.hpp"
#include "layers.hpp"
#include "renderer/shaderBuilder.hpp"

namespace engine {
  class App {
    private:
      bool isRunning = true;
      bool useImGui = false;
      float timePreviousFrame = 0.0f;
      static App* instance;

      unsigned int vertexArray;
      unsigned int vertexBuffer;
      unsigned int indexBuffer;

    public:
      std::unique_ptr<Window> window;
      std::shared_ptr<EventBus> eventBus;
      std::unique_ptr<Layer> imGuiLayer;
      std::unique_ptr<Shader> shader;
      Layers layers;
      
      App(bool useImGui);
      virtual ~App() = default;
      void run();
      void close();
      void resize(const WindowResizedEvent& event);
      void event(Event& event);
      static App& get();
  };
}

#endif
