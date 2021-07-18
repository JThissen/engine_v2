#ifndef IMGUI_LAYER_H
#define IMGUI_LAYER_H

// #include "engine.hpp"
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "app.hpp"

namespace engine {
  class ImGuiLayer : public Layer {
    public:
    ImGuiLayer();
    virtual ~ImGuiLayer() = default;
    virtual void push() override;
    virtual void remove() override;
    virtual void update(DeltaTime deltaTime) override;
    virtual void event(Event& event) override;

    void mousePressedEvent(MousePressedEvent& event);
    void mouseReleasedEvent(MouseReleasedEvent& event);
    void mouseScrolledEvent(MouseScrolledEvent& event);
    void mousePositionEvent(MousePositionEvent& event);
    void windowResizedEvent(WindowResizedEvent& event);
  };
}

#endif
