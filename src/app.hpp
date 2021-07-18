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
    
    public:
      std::unique_ptr<Window> window;
      std::shared_ptr<EventBus> eventBus;
      Layers layers;
      
      static App& get();
      App();
      virtual ~App() = default;
      void run();
      void close();
      void resize(const WindowResizedEvent& event);
      void event(Event& event);
      void pushLayer(std::unique_ptr<Layer>& layer);

      private:
      static App* instance;
  };
}

#endif
