#include "layers.hpp"

namespace engine {
  void Layers::pushLayer(std::shared_ptr<Layer> layer) {
    layer->push();
    layers.push_back(layer);
  }

  void Layers::removeLayer(std::shared_ptr<Layer> layer) {
    auto iter = std::find(layers.begin(), layers.end(), layer);
    
    if(iter != layers.end()) {
      layer->remove();
      layers.erase(iter);
    }
  }

  void Layers::pushOverlay(std::shared_ptr<Layer> overlay) {
    overlays.push_back(overlay);
  }

  void Layers::removeOverlay(std::shared_ptr<Layer> overlay) {
    auto iter = std::find(overlays.begin(), overlays.end(), overlay);
    
    if(iter != overlays.end()) {
      overlay->remove();
      overlays.erase(iter);
    }
  }
}
