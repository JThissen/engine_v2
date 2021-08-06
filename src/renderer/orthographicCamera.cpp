#include "orthographicCamera.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace engine {
  OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top) 
    : projectionMatrix(glm::ortho(left, right, bottom, top)) {

  }

  void OrthographicCamera::setProjectionMatrix(float left, float right, float bottom, float top) {
    projectionMatrix = glm::ortho(left, right, bottom, top);
  }

  void OrthographicCamera::calculateViewMatrix() {
    glm::mat4 worldMatrix = glm::translate(glm::mat4(1.0f), position) * 
      glm::rotate(glm::mat4(1.0f), glm::radians(rotationInDegrees), glm::vec3(0.0f, 0.0f, 1.0f));

    viewMatrix = glm::inverse(worldMatrix);
  }

  void OrthographicCamera::setPosition(const glm::vec3 position) {
    this->position = position;
    calculateViewMatrix();
  }

  void OrthographicCamera::setRotation(float rotationInDegrees) {
    this->rotationInDegrees = rotationInDegrees;
    calculateViewMatrix();
  }
}