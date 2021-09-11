#ifndef SCENE_H
#define SCENE_H

#include "../headers.hpp"
#include <entt.hpp>
#include "component.hpp"
#include "../opengl/openglRenderer.hpp"
#include "../renderer/perspectiveCamera.hpp"

namespace engine {
  class Scene {
    private:
    std::shared_ptr<OpenglRenderer> openglRenderer;
    float rotation = 0.0f;

    public:
    entt::registry registry;
    entt::entity entity;
    Scene(std::shared_ptr<OpenglRenderer> openglRenderer);
    void update(float time, DeltaTime deltaTime);
    void createEntity(const std::string& name = "Entity");

    template<typename T1, typename... T2> 
    T1& addComponent(T2&&... args) {
      return registry.emplace<T1>(entity, std::forward<T2>(args)...);
    }

    template<typename T>
    T& getComponent() {
      return registry.get<T>(entity);
    }

    template<typename T>
    void removeComponent() {
      registry.remove<T>(entity);
    }
  };
}

#endif