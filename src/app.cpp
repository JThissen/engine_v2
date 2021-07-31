#include "app.hpp"
#include "windowInput.hpp"
#include "imGuiLayer.hpp"

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

    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);
    
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    std::array<float, 15> vertices=  {
      -0.5f, -0.5f, 0.0f,
      0.5f, -0.5f, 0.0f,
      0.0f, 0.5f, 0.0f,
      0.5f, 0.5f, 0.0f,
      -0.5f, 0.5f, 0.0f
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    std::array<int, 9> indices = { 0, 1, 2, 1, 3, 2, 0, 2, 4};
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr);

    glPolygonMode(GL_FRONT, GL_LINE);

    ShaderBuilder shaderBuilder;
    shaderBuilder.createProgram()
      .attachVertexShader("./../src/shaders/test.vs")
      .attachFragmentShader("./../src/shaders/test.fs")
      .linkProgram();
    shader = std::move(shaderBuilder.shader);
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
      glBindVertexArray(vertexArray);
      glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, nullptr);

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
