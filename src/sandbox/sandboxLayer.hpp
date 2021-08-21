#ifndef SANDBOX_LAYER_H
#define SANDBOX_LAYER_H

#include "../engine.hpp"

class SandboxLayer : public engine::Layer {
  public:
  SandboxLayer();
  virtual ~SandboxLayer() = default;
  virtual void push() override;
  virtual void remove() override;
  virtual void update(float time, engine::DeltaTime deltaTime) override;
  virtual void event(engine::Event& event) override;
  virtual void createImGuiLayout() override;

  private:
  std::shared_ptr<engine::OpenglVertexArray> openglVertexArray;
  std::shared_ptr<engine::Shader> shader;
  std::shared_ptr<engine::OpenglRenderer> openglRenderer;
  // std::unique_ptr<engine::OrthographicCamera> orthographicCamera;
  std::unique_ptr<engine::OrthographicCameraController> orthographicCameraController;
  std::unique_ptr<engine::PerspectiveCamera> perspectiveCamera;
  std::unique_ptr<engine::OpenglTexture> texture, texture2;

  std::shared_ptr<engine::OpenglVertexArray> openglVertexArray2;
  std::shared_ptr<engine::Shader> shader2;
  glm::vec3 position2 = glm::vec3(0.0f);
  float speed2 = 1.0f;

  float orthographicCameraTranslationSpeed = 1.0f;
  float orthographicCameraRotationSpeed = 200.0f;

  glm::vec3 color = { 0.0f, 1.0f, 0.0f };

  std::pair<float ,float> mousePosition = { 400.0f, 300.0f };

  bool hasMouseEnterWindow = false;
};

#endif
