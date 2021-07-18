#include "layers.hpp"

namespace engine {
  void Layers::pushLayer(std::unique_ptr<Layer>& layer) {
    layers.push_back(std::move(layer));
  }

  void Layers::removeLayer(std::unique_ptr<Layer>& layer) {
    auto iter = std::find(layers.begin(), layers.end(), layer);
    
    if(iter != layers.end()) {
      layer->remove();
      layers.erase(iter);
    }
  }

  void Layers::pushOverlay(std::unique_ptr<Layer>& overlay) {
    overlays.push_back(std::move(overlay));
  }

  void Layers::removeOverlay(std::unique_ptr<Layer>& overlay) {
    auto iter = std::find(overlays.begin(), overlays.end(), overlay);
    
    if(iter != overlays.end()) {
      overlay->remove();
      overlays.erase(iter);
    }
  }
}
