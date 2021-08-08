#ifndef LAYERS_H
#define LAYERS_H

#include "headers.hpp"
#include "layer.hpp"

namespace engine {
  class Layers {
    public:
    std::vector<std::shared_ptr<Layer>> layers;
    std::vector<std::shared_ptr<Layer>> overlays;

    Layers() = default;
    ~Layers() = default;
    void pushLayer(std::shared_ptr<Layer> layer);
    void removeLayer(std::shared_ptr<Layer> layer);
    void pushOverlay(std::shared_ptr<Layer> overlay);
    void removeOverlay(std::shared_ptr<Layer> overlay);
  };
}

#endif
