#include "perspectiveCamera.hpp"
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/quaternion.hpp>
#include "../utils.hpp"

namespace engine {
  PerspectiveCamera::PerspectiveCamera(float windowWidth, float windowHeight, float speed, float fov, float sensitivity) {
    aspectRatio = windowWidth / windowHeight;
    view = glm::lookAt(position, position + z, y);
    projection = glm::perspective(glm::radians(fov), aspectRatio, 0.1f, 1000.0f);
  }

  void PerspectiveCamera::handleKeyPress(DeltaTime deltaTime) {
    if(WindowInput::isKeyPressed(Key::KeyCode::A)) {
      position += glm::normalize(glm::cross(z, y)) * speed * deltaTime.seconds();
    } else if(WindowInput::isKeyPressed(Key::KeyCode::D)) {
      position -= glm::normalize(glm::cross(z, y)) * speed * deltaTime.seconds();
    }
    if(WindowInput::isKeyPressed(Key::KeyCode::S)) {
      position += z * speed * deltaTime.seconds();
    } else if(WindowInput::isKeyPressed(Key::KeyCode::W)) {
      position -= z * speed * deltaTime.seconds();
    }
  }

  void PerspectiveCamera::updateView(DeltaTime deltaTime, std::pair<float, float> mousePosition, bool hasMouseEnterWindow) {
    handleKeyPress(deltaTime);
    if(hasMouseEnterWindow && first) {
      previousMousePosition.first = mousePosition.first;
      previousMousePosition.second = mousePosition.second; 
      first = false;
    }
    float dx = mousePosition.first - previousMousePosition.first;
    float dy = previousMousePosition.second - mousePosition.second;
    previousMousePosition.first = mousePosition.first;
    previousMousePosition.second = mousePosition.second;
    dx *= sensitivity;
    dy *= sensitivity;
    yaw += dx;
    pitch += dy;

    glm::quat qPitch = glm::angleAxis(glm::radians(-pitch), glm::vec3(1, 0, 0));
    glm::quat qYaw = glm::angleAxis(glm::radians(yaw), glm::vec3(0, 1, 0));
    glm::quat qPitchYaw = glm::normalize(qPitch * qYaw);
    glm::mat4 rotate = glm::toMat4(qPitchYaw);
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), position);
    view = rotate * translate;
    x = glm::rotate(glm::inverse(qPitchYaw), glm::vec3(1.0, 0.0, 0.0));
    z = glm::rotate(glm::inverse(qPitchYaw), glm::vec3(0.0, 0.0, -1.0));
  }
}