#include "layer.hpp"

namespace engine {
  Layer::Layer(const std::string& name) : name(name) {}

  void Layer::event(Event& event) {
    // maybe for later usage
  }

  void Layer::createImGuiLayout() {}
}
