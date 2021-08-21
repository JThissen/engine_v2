#ifndef IMGUI_LAYER_H
#define IMGUI_LAYER_H

#include "layer.hpp"

namespace engine {
  class ImGuiLayer : public Layer {
    public:
    ImGuiLayer();
    virtual ~ImGuiLayer() = default;
    virtual void push() override;
    virtual void remove() override;
    virtual void update(float time, DeltaTime deltaTime) override;
    virtual void event(Event& event) override;
    void render();
    void newFrame();
  };
}

#endif
