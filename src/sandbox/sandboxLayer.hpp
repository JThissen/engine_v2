#ifndef SANDBOX_LAYER_H
#define SANDBOX_LAYER_H

#include "../engine.hpp"

class SandboxLayer : public engine::Layer {
  public:
  SandboxLayer();
  virtual ~SandboxLayer() = default;
  virtual void push() override;
  virtual void remove() override;
  virtual void update(engine::DeltaTime deltaTime) override;
  virtual void event(engine::Event& event) override;

  private:
  std::shared_ptr<engine::OpenglVertexArray> openglVertexArray;
  std::unique_ptr<engine::Shader> shader;
  std::unique_ptr<engine::OpenglRenderer> openglRenderer;
  std::unique_ptr<engine::OrthographicCamera> orthographicCamera;
};

#endif
