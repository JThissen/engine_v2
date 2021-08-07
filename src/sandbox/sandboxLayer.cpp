#include "sandboxLayer.hpp"
#include <glm/gtc/type_ptr.hpp>

  SandboxLayer::SandboxLayer() : Layer("sandboxLayer") {
    openglVertexArray = std::make_unique<engine::OpenglVertexArray>();

    std::array<float, 9> vertices = {
      -0.5f, -0.5f, 0.0f,
      0.5f, -0.5f, 0.0f,
      0.0f, 0.5f, 0.0f,
    };
    auto openglVertexBuffer = std::make_shared<engine::OpenglVertexBuffer>(
      vertices.data(),
      vertices.size(),
      engine::LayoutBuffer({
        { engine::GLSLType::VEC3, "in_position" }
      })
    );
    openglVertexArray->pushVertexBuffer(openglVertexBuffer);

    std::array<int, 3> indices = { 0, 1, 2 };
    auto openglIndexBuffer = std::make_shared<engine::OpenglIndexBuffer>(indices.data(), indices.size());
    openglVertexArray->setIndexBuffer(openglIndexBuffer);

    engine::ShaderBuilder shaderBuilder;
    shaderBuilder.createProgram()
      .attachVertexShader("./../src/shaders/test.vs")
      .attachFragmentShader("./../src/shaders/test.fs")
      .linkProgram();
    shader = std::move(shaderBuilder.shader);
    // glPolygonMode(GL_FRONT, GL_LINE);

    openglRenderer = std::make_unique<engine::OpenglRenderer>();
    orthographicCamera = std::make_unique<engine::OrthographicCamera>(-2.0f, 2.0f, -2.0f, 2.0f);
  }

  void SandboxLayer::push() {
    // t.b.d.
  }

  void SandboxLayer::remove() {
    // t.b.d.
  }

  void SandboxLayer::update(engine::DeltaTime deltaTime) {
    openglRenderer->setClearColor(0.24f, 0.24f, 0.24f, 1.0f);
    openglRenderer->clear();

    orthographicCamera->setPosition(glm::vec3(glm::sin(glfwGetTime()), 0.0f, 0.0f));

    shader->useProgram();
    glUniform1f(glGetUniformLocation(shader->program, "time"), static_cast<float>(glfwGetTime()));
    glUniformMatrix4fv(glGetUniformLocation(shader->program, "viewMatrix"), 1, GL_FALSE, glm::value_ptr(orthographicCamera->viewMatrix));
    glUniformMatrix4fv(glGetUniformLocation(shader->program, "projectionMatrix"), 1, GL_FALSE, glm::value_ptr(orthographicCamera->projectionMatrix));
    
    openglVertexArray->bind();
    openglRenderer->draw(openglVertexArray);
  }

  void SandboxLayer::event(engine::Event& event) {
    // t.b.d.
  }
