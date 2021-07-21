#ifndef APP_H
#define APP_H

#include "headers.hpp"
#include "window.hpp"
#include "eventBus.hpp"
#include "layers.hpp"

namespace engine {
  class App {
    private:
      bool running = true;
      float timePreviousFrame = 0.0f;
      static App* instance;
    
    public:
      bool useImGui = true;
      std::unique_ptr<Window> window;
      std::shared_ptr<EventBus> eventBus;
      std::unique_ptr<Layer> imGuiLayer;
      Layers layers;
      
      static App& get();
      App();
      virtual ~App() = default;
      void run();
      void close();
      void resize(const WindowResizedEvent& event);
      void event(Event& event);
  };
}

#endif
