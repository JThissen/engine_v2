#ifndef COMPONENT_H
#define COMPONENT_H

#include "../headers.hpp"
#include <glm/glm.hpp>
#include "../opengl/openglTexture.hpp"

namespace engine {
  class NameComponent {
    public:
    std::string name;

    NameComponent() = default;
    NameComponent(const NameComponent& other) = default;
    NameComponent(const std::string& name);
  };

  class TransformComponent {
    public:
    glm::vec3 x = { 1.0f, 0.0f, 0.0f };
    glm::vec3 y = { 0.0f, 1.0f, 0.0f };
    glm::vec3 z = { 0.0f, 0.0f, -1.0f };

    glm::vec3 translate = { 0.0f, 0.0f, 0.0f };
    glm::vec3 rotate = { 0.0f, 0.0f, 0.0f }; //euler angles in radians
    glm::vec3 scale = { 1.0f, 1.0f, 1.0f };

    TransformComponent() = default;
    TransformComponent(const TransformComponent& other) = default;
    glm::mat4 trs();
  };

  class TextureComponent {
    public:
		glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };
    std::shared_ptr<OpenglTexture> texture;
		// float TilingFactor = 1.0f;

		TextureComponent() = default;
		TextureComponent(const TextureComponent& other) = default;
	};
}

#endif