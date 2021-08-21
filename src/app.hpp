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
      bool isRunning = true;
      bool useImGui = false;
      float time = 0.0f;
      float timePreviousFrame = 0.0f;
      DeltaTime deltaTime;
      static App* instance;

      unsigned int vertexArray;
      unsigned int vertexBuffer;
      unsigned int indexBuffer;

    public:
      std::unique_ptr<Window> window;
      std::shared_ptr<EventBus> eventBus;
      std::shared_ptr<ImGuiLayer> imGuiLayer;
      std::shared_ptr<Layer> testLayer;
      std::unique_ptr<Shader> shader;
      std::unique_ptr<Shader> shader2;
      std::shared_ptr<OpenglVertexArray> openglVertexArray;
      std::unique_ptr<OpenglVertexArray> testVA;
      std::unique_ptr<OpenglRenderer> openglRenderer;
      std::unique_ptr<OrthographicCamera> orthographicCamera;
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
