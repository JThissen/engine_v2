#include "perspectiveCamera.hpp"
#include <glm/gtx/string_cast.hpp>
#include "../utils.hpp"

namespace engine {
  PerspectiveCamera::PerspectiveCamera(float windowWidth, float windowHeight, float speed, float fov, float sensitivity) {
    aspectRatio = windowWidth / windowHeight;
    view = glm::lookAt(position, position + z, y);
    projection = glm::perspective(glm::radians(fov), aspectRatio, 0.1f, 1000.0f);
  }

  void PerspectiveCamera::handleKeyPress(DeltaTime deltaTime) {
    if(WindowInput::isKeyPressed(Key::KeyCode::A)) {
      position -= glm::normalize(glm::cross(z, y)) * speed * deltaTime.seconds();
    } else if(WindowInput::isKeyPressed(Key::KeyCode::D)) {
      position += glm::normalize(glm::cross(z, y)) * speed * deltaTime.seconds();
    }
    if(WindowInput::isKeyPressed(Key::KeyCode::S)) {
      position -= z * speed * deltaTime.seconds();
    } else if(WindowInput::isKeyPressed(Key::KeyCode::W)) {
      position += z * speed * deltaTime.seconds();
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
    pitch = (pitch > 89.0f) ? 89.0f : (pitch < -89.0f) ? -89.0f : pitch;
    z = {
      cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
      sin(glm::radians(pitch)),
      sin(glm::radians(yaw)) * cos(glm::radians(pitch))
    };
    view = glm::lookAt(position, position + glm::normalize(z), y);
  }
}