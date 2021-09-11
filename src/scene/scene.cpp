#include "scene.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace engine {
  Scene::Scene(std::shared_ptr<OpenglRenderer> openglRenderer) : openglRenderer(openglRenderer) {
  }

  void Scene::createEntity(const std::string& name) {
    entity = registry.create();
    auto& nameComponent = addComponent<NameComponent>();
    nameComponent.name = nameComponent.name.empty() ? "Entity" : name;
    addComponent<TransformComponent>();
  }

  void Scene::update(float time, DeltaTime deltaTime) {
    rotation += 10.0f * deltaTime;
    auto& transformComponent = registry.get<TransformComponent>(entity);
    transformComponent.translate = glm::vec3(1.0f, 0.0, 0.0f);
    transformComponent.rotate = glm::vec3(0.0f, 0.0f, glm::radians(rotation));
    auto& textureComponent = registry.get<TextureComponent>(entity);
    // openglRenderer->drawQuad(transformComponent.trs(), textureComponent.color);
    openglRenderer->drawQuad(transformComponent.trs(), textureComponent.texture);
    openglRenderer->drawQuad(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, 0.0f)), textureComponent.texture);
    // openglRenderer->drawQuad(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 1.0f)), textureComponent.texture);

    // openglRenderer->drawQuad(glm::translate(glm::mat4(1.0f), glm::vec3(-1.5f, 0.0f, 0.0f)), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
  }
}