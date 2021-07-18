#ifndef LAYERS_H
#define LAYERS_H

#include "headers.hpp"
#include "layer.hpp"

namespace engine {
  class Layers {
    public:
    std::vector<std::unique_ptr<Layer>> layers;
    std::vector<std::unique_ptr<Layer>> overlays;

    Layers() = default;
    ~Layers() = default;
    void pushLayer(std::unique_ptr<Layer>& layer);
    void removeLayer(std::unique_ptr<Layer>& layer);
    void pushOverlay(std::unique_ptr<Layer>& overlay);
    void removeOverlay(std::unique_ptr<Layer>& overlay);
  };
}

#endif
