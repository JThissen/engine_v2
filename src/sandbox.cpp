#include "sandbox.hpp"

Sandbox::Sandbox(bool useImGui) : App(useImGui) {
  std::unique_ptr<engine::Layer> testLayer = std::make_unique<TestLayer>();
  layers.pushLayer(testLayer);
}
