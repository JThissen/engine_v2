#include "sandbox.hpp"

Sandbox::Sandbox(bool useImGui) : App(useImGui) {
  std::unique_ptr<engine::Layer> sandboxLayer = std::make_unique<SandboxLayer>();
  layers.pushLayer(sandboxLayer);
  run();
}
