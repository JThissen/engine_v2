#include "sandboxLayer.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include "../imgui/imgui.h"
#include "../utils.hpp"
#include "../mouseEvent.hpp"
#include "../app.hpp"
#include <glad/glad.h>

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

    openglRenderer = std::make_shared<engine::OpenglRenderer>();
    openglRenderer->init();
    // orthographicCamera = std::make_unique<engine::OrthographicCamera>(-1.0f, 1.0f, -1.0f, 1.0f);
    // orthographicCameraController = std::make_unique<engine::OrthographicCameraController>(
    //   static_cast<float>(engine::App::get().window->width / engine::App::get().window->height));
    perspectiveCamera = std::make_unique<engine::PerspectiveCamera>(800.0f, 600.0f);
    openglVertexArray2 = std::make_unique<engine::OpenglVertexArray>();

    // std::array<float, 20> vertices2 = {
    //   -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    //   -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
    //   0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
    //   0.5f, 0.5f, 0.0f, 1.0f, 1.0f
    // };
    std::array<float, 20> ndc = {
      -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
      -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
      1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
      1.0f, 1.0f, 0.0f, 1.0f, 1.0f
    };
    auto openglVertexBuffer2 = std::make_shared<engine::OpenglVertexBuffer>(
      ndc.data(),
      ndc.size(),
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

    texture = std::make_unique<engine::OpenglTexture>("./../src/sandbox/assets/checkerboard.png");
    shader2->setUniform1i(0, "testTexture"); //we can bind unit 1, 2, 3 etc
    texture2 = std::make_unique<engine::OpenglTexture>("./../src/sandbox/assets/wood.jpg");


    engine::ShaderBuilder shaderBuilder3;
    shaderBuilder3.createProgram()
      .attachVertexShader("./../src/shaders/basic.vs")
      .attachFragmentShader("./../src/shaders/basic.fs")
      .linkProgram();
    shader3 = std::move(shaderBuilder3.shader);

    frameBuffer = std::make_unique<engine::FrameBuffer>(800, 600, 1, true);
  }

  void SandboxLayer::push() {
    // t.b.d.
  }

  void SandboxLayer::remove() {
    // t.b.d.
  }

  void SandboxLayer::update(float time, engine::DeltaTime deltaTime) {
    frameBuffer->bind();
    openglRenderer->setClearColor(0.24f, 0.24f, 0.24f, 1.0f);
    openglRenderer->clear();
    // openglRenderer->setViewport(0, 0, 1920, 1068);
    perspectiveCamera->updateView(deltaTime, mousePosition, hasMouseEnterWindow);

    // openglRenderer->draw(
    //   shader,
    //   glm::mat4(1.0f),
    //   orthographicCamera->viewMatrix,
    //   orthographicCamera->projectionMatrix,
    //   openglVertexArray
    // );

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

    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), position2) * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
    shader2->setUniform4f(glm::vec4(color, 1.0f), "col");
    texture->bind(0);
    openglRenderer->draw(
      shader2,
      modelMatrix,
      perspectiveCamera->view,
      perspectiveCamera->projection,
      openglVertexArray2
    );
    texture2->bind(0);
    openglRenderer->draw(
      shader2,
      glm::translate(glm::mat4(1.0f), glm::vec3(0.25f, 0.25f, -1.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f)),
      perspectiveCamera->view,
      perspectiveCamera->projection,
      openglVertexArray2
    );
    frameBuffer->unbind();

    openglRenderer->setClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    openglRenderer->clear();
    frameBuffer->bindTexture(frameBuffer->colorAttachmentIds[0]);
    openglRenderer->draw(
      shader3,
      glm::mat4(),
      glm::mat4(),
      glm::mat4(),
      openglVertexArray2
    );
  }

  void SandboxLayer::createImGuiLayout() {
    ImGui::Begin("test");
    ImGui::ColorPicker3("square color",  glm::value_ptr(color));
    ImGui::End();
  }

  void SandboxLayer::event(engine::Event& event) {
    if(event.eventType == engine::Event::EventType::MouseScrolled) {
      try {
        // orthographicCameraController->mouseScroll(dynamic_cast<engine::MouseScrolledEvent&>(event));
      } catch(const std::bad_cast& error) {
        std::cout << error.what() << std::endl;
      }
    } else if(event.eventType == engine::Event::EventType::WindowResized) {
      auto windowResizedEvent = dynamic_cast<engine::WindowResizedEvent&>(event);
      engine::Utils::print(windowResizedEvent.width, windowResizedEvent.height);
      // orthographicCameraController->resize(windowResizedEvent);
      // openglRenderer->setViewport(0, 0, windowResizedEvent.width, windowResizedEvent.height);
    } else if(event.eventType == engine::Event::EventType::FramebufferResized) {
      // engine::Utils::print("test", event.getSize().first, event.getSize().second);
      // auto frameBufferResizedEvent = dynamic_cast<engine::FramebufferResizedEvent&>(event);
      // openglRenderer->setViewport(0, 0, frameBufferResizedEvent.width, frameBufferResizedEvent.height);
    } else if(event.eventType == engine::Event::EventType::MousePosition) {
      auto mousePositionEvent = dynamic_cast<engine::MousePositionEvent&>(event);
      mousePosition = { static_cast<float>(mousePositionEvent.x), static_cast<float>(mousePositionEvent.y) };
      hasMouseEnterWindow = true;
    }
  }
