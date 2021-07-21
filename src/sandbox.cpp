#include "sandbox.hpp"

Sandbox::Sandbox() {
  std::unique_ptr<engine::Layer> testLayer = std::make_unique<TestLayer>();
  layers.pushLayer(testLayer);
}
