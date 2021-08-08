#include "sandbox.hpp"

Sandbox::Sandbox(bool useImGui) : App(useImGui) {
  std::shared_ptr<engine::Layer> sandboxLayer = std::make_shared<SandboxLayer>();
  layers.pushLayer(sandboxLayer);
  run();
}
