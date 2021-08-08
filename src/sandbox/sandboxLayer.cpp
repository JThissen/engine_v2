#include "sandboxLayer.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "../imgui/imgui.h"

  SandboxLayer::SandboxLayer() : Layer("sandboxLayer") {
    // openglVertexArray = std::make_unique<engine::OpenglVertexArray>();

    // std::array<float, 9> vertices = {
    //   -0.5f, -0.5f, 0.0f,
    //   0.5f, -0.5f, 0.0f,
    //   0.0f, 0.5f, 0.0f,
    // };
    // auto openglVertexBuffer = std::make_shared<engine::OpenglVertexBuffer>(
    //   vertices.data(),
    //   vertices.size(),
    //   engine::LayoutBuffer({
    //     { engine::GLSLType::VEC3, "in_position" }
    //   })
    // );
    // openglVertexArray->pushVertexBuffer(openglVertexBuffer);

    // std::array<int, 3> indices = { 0, 1, 2 };
    // auto openglIndexBuffer = std::make_shared<engine::OpenglIndexBuffer>(indices.data(), indices.size());
    // openglVertexArray->setIndexBuffer(openglIndexBuffer);

    // engine::ShaderBuilder shaderBuilder;
    // shaderBuilder.createProgram()
    //   .attachVertexShader("./../src/shaders/test.vs")
    //   .attachFragmentShader("./../src/shaders/test.fs")
    //   .linkProgram();
    // shader = std::move(shaderBuilder.shader);
    // glPolygonMode(GL_FRONT, GL_LINE);

    openglRenderer = std::make_unique<engine::OpenglRenderer>();
    orthographicCamera = std::make_unique<engine::OrthographicCamera>(-1.0f, 1.0f, -1.0f, 1.0f);

    openglVertexArray2 = std::make_unique<engine::OpenglVertexArray>();

    std::array<float, 20> vertices2 = {
      -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
      -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
      0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
      0.5f, 0.5f, 0.0f, 1.0f, 1.0f
    };
    auto openglVertexBuffer2 = std::make_shared<engine::OpenglVertexBuffer>(
      vertices2.data(),
      vertices2.size(),
      engine::LayoutBuffer({
        { engine::GLSLType::VEC3, "layoutPosition" },
        { engine::GLSLType::VEC2, "layoutTextureCoords" }
      })
    );
    openglVertexArray2->pushVertexBuffer(openglVertexBuffer2);

    std::array<int, 6> indices2 = { 0, 1, 2, 0, 2, 3 };
    auto openglIndexBuffer2 = std::make_shared<engine::OpenglIndexBuffer>(indices2.data(), indices2.size());
    openglVertexArray2->setIndexBuffer(openglIndexBuffer2);

    engine::ShaderBuilder shaderBuilder2;
    shaderBuilder2.createProgram()
      .attachVertexShader("./../src/shaders/test.vs")
      .attachFragmentShader("./../src/shaders/test.fs")
      .linkProgram();
    shader2 = std::move(shaderBuilder2.shader);

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

    // if(engine::WindowInput::isKeyPressed(engine::Key::KeyCode::A)) {
    //   orthographicCamera->position.x += orthographicCameraTranslationSpeed * deltaTime.seconds();
    // } else if(engine::WindowInput::isKeyPressed(engine::Key::KeyCode::D)) {
    //   orthographicCamera->position.x -= orthographicCameraTranslationSpeed * deltaTime.seconds();
    // }
    // if(engine::WindowInput::isKeyPressed(engine::Key::KeyCode::W)) {
    //   orthographicCamera->position.y -= orthographicCameraTranslationSpeed * deltaTime.seconds();
    // } else if(engine::WindowInput::isKeyPressed(engine::Key::KeyCode::S)) {
    //   orthographicCamera->position.y += orthographicCameraTranslationSpeed * deltaTime.seconds();
    // }

    orthographicCamera->calculateViewMatrix();

    // openglRenderer->draw(
    //   shader,
    //   glm::mat4(1.0f),
    //   orthographicCamera->viewMatrix,
    //   orthographicCamera->projectionMatrix,
    //   openglVertexArray
    // );

    if(engine::WindowInput::isKeyPressed(engine::Key::KeyCode::J)) {
      position2.x += speed2 * deltaTime.seconds();
    } else if(engine::WindowInput::isKeyPressed(engine::Key::KeyCode::L)) {
      position2.x -= speed2 * deltaTime.seconds();
    }
    if(engine::WindowInput::isKeyPressed(engine::Key::KeyCode::K)) {
      position2.y += speed2 * deltaTime.seconds();
    } else if(engine::WindowInput::isKeyPressed(engine::Key::KeyCode::I)) {
      position2.y -= speed2 * deltaTime.seconds();
    }

    // for(int i = 0; i < 5; i++) {
    //   for(int j = 0; j < 5; j++) {
    //     glm::vec3 newPos = position2 + glm::vec3(i * 0.22f, j * 0.22f, 0.0f);
    //     glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(newPos));
    //     glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.2f));
    //     glm::mat4 modelMatrix = translate * scale;
    //     shader2->setUniform4f(glm::vec4(color, 1.0f), "col");
    //     openglRenderer->draw(
    //       shader2,
    //       modelMatrix,
    //       orthographicCamera->viewMatrix,
    //       orthographicCamera->projectionMatrix,
    //       openglVertexArray2
    //     );
    //   }
    // }

    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
    glm::mat4 modelMatrix = scale;
    shader2->setUniform4f(glm::vec4(color, 1.0f), "col");
    openglRenderer->draw(
      shader2,
      modelMatrix,
      orthographicCamera->viewMatrix,
      orthographicCamera->projectionMatrix,
      openglVertexArray2
    );
  }

  void SandboxLayer::createImGuiLayout() {
    ImGui::Begin("test");
    ImGui::ColorPicker3("square color",  glm::value_ptr(color));
    ImGui::End();
  }

  void SandboxLayer::event(engine::Event& event) {
    // t.b.d.
  }
