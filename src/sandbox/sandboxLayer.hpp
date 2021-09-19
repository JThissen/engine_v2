#ifndef SANDBOX_LAYER_H
#define SANDBOX_LAYER_H

#include "../engine.hpp"

class SandboxLayer : public engine::Layer {
  public:
  SandboxLayer(int windowWidth, int windowHeight);
  virtual ~SandboxLayer() = default;
  virtual void push() override;
  virtual void remove() override;
  virtual void update(float time, engine::DeltaTime deltaTime) override;
  virtual void event(engine::Event& event) override;
  virtual void createImGuiLayout() override;
  void setViewportMousePosition();
  void setObjectSelectedId();

  private:
  std::unique_ptr<engine::FrameBuffer> frameBuffer;
  std::unique_ptr<engine::FrameBuffer> frameBuffer2;
  std::shared_ptr<engine::OpenglRenderer> openglRenderer;
  std::shared_ptr<engine::PerspectiveCamera> editorCamera;
  // std::shared_ptr<engine::OrthographicCamera> orthographicCamera;
  std::shared_ptr<engine::OpenglTexture> texture;
  std::unique_ptr<engine::Scene> scene;
  glm::vec2 viewportDimensions;
  glm::vec2 viewportBounds[2];
  glm::vec2 mousePosition;
  glm::vec2 viewportMousePosition = { 0.0, 0.0 };
  glm::vec2 viewportSize = { 0.0, 0.0 };
  bool hasMouseEnterWindow = false;
  bool autoScroll = true;
  int objectSelectedId = -1;
};

#endif
