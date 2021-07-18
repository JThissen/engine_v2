#ifndef TEST_LAYER_H
#define TEST_LAYER_H

#include "engine.hpp"

class TestLayer : public engine::Layer {
  public:
  TestLayer();
  virtual ~TestLayer() = default;
  virtual void push() override;
  virtual void remove() override;
  virtual void update(engine::DeltaTime deltaTime) override;
  virtual void event(engine::Event& event) override;
};

#endif
