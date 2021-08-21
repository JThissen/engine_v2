#ifndef LAYER_H
#define LAYER_H

#include "headers.hpp"
#include "deltaTime.hpp"
#include "event.hpp"

namespace engine {
  class Layer {
    public:
    std::string name;
    Layer(const std::string& name);
    virtual ~Layer() = default;
    virtual void push() = 0;
    virtual void remove() = 0;
    virtual void update(float time, DeltaTime deltaTime) = 0;
    virtual void event(Event& event) = 0;
    virtual void createImGuiLayout();
  };
}

#endif
