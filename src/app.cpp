#include "app.hpp"
#include "windowInput.hpp"
#include "imGuiLayer.hpp"
#include "renderer/layoutBuffer.hpp"

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
    openglVertexArray = std::make_unique<OpenglVertexArray>();

    std::array<float, 9> vertices = {
      -0.5f, -0.5f, 0.0f,
      0.5f, -0.5f, 0.0f,
      0.0f, 0.5f, 0.0f,
    };
    auto openglVertexBuffer = std::make_shared<OpenglVertexBuffer>(
      vertices.data(),
      vertices.size(),
      LayoutBuffer({
        { GLSLType::VEC3, "in_position" }
      })
    );
    openglVertexArray->pushVertexBuffer(openglVertexBuffer);

    std::array<int, 3> indices = { 0, 1, 2 };
    auto openglIndexBuffer = std::make_shared<OpenglIndexBuffer>(indices.data(), indices.size());
    openglVertexArray->setIndexBuffer(openglIndexBuffer);

    ShaderBuilder shaderBuilder;
    shaderBuilder.createProgram()
      .attachVertexShader("./../src/shaders/test.vs")
      .attachFragmentShader("./../src/shaders/test.fs")
      .linkProgram();
    shader = std::move(shaderBuilder.shader);
    // glPolygonMode(GL_FRONT, GL_LINE);
  }

  void App::run() {
    while(isRunning) {
      float time = static_cast<float>(glfwGetTime());
      DeltaTime deltaTime = DeltaTime(time - timePreviousFrame);
      timePreviousFrame = time;

      glClearColor(0.24f, 0.24f, 0.24f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);
      glUniform1f(glGetUniformLocation(shader->program, "time"), time);
      shader->useProgram();
      openglVertexArray->bind();
      glBindVertexArray(openglVertexArray->vertexArray);
      glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

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
