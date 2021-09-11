#include "component.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtx/quaternion.hpp>

namespace engine {
  glm::mat4 TransformComponent::trs() {
      return glm::translate(glm::mat4(1.0f), translate)
        * glm::toMat4(glm::quat(rotate))
        * glm::scale(glm::mat4(1.0f), scale);
    }

  NameComponent::NameComponent(const std::string& name)
    : name(name) {}
}
