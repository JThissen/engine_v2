#include "sandbox.hpp"

Sandbox::Sandbox() {
  std::unique_ptr<engine::Layer> testLayer = std::make_unique<TestLayer>();
  std::unique_ptr<engine::Layer> imGuiLayer = std::make_unique<engine::ImGuiLayer>();
  pushLayer(testLayer);
  pushLayer(imGuiLayer);
}
