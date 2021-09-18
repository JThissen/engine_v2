#include "perspectiveCamera.hpp"
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/quaternion.hpp>
#include "../utils.hpp"

namespace engine {
  PerspectiveCamera::PerspectiveCamera(float windowWidth, float windowHeight, float speed, float fov, float sensitivity, float zoomSpeed, float nearPlane, float farPlane)
    : aspectRatio(windowWidth/ windowHeight), speed(speed), fov(fov), sensitivity(sensitivity), zoomSpeed(zoomSpeed), nearPlane(nearPlane), farPlane(farPlane) {
    view = glm::lookAt(position, position + z, y);
    projection = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
  }

  void PerspectiveCamera::handleKeyPress(DeltaTime deltaTime) {
    if(WindowInput::isKeyPressed(Key::KeyCode::A)) {
      position -= glm::normalize(glm::cross(y, z)) * speed * deltaTime.seconds();
    } else if(WindowInput::isKeyPressed(Key::KeyCode::D)) {
      position += glm::normalize(glm::cross(y, z)) * speed * deltaTime.seconds();
    }
    if(WindowInput::isKeyPressed(Key::KeyCode::S)) {
      position += z * speed * deltaTime.seconds();
    } else if(WindowInput::isKeyPressed(Key::KeyCode::W)) {
      position -= z * speed * deltaTime.seconds();
    }
  }

  void PerspectiveCamera::updateView(DeltaTime deltaTime, const glm::vec2& mousePosition, bool hasMouseEnterWindow) {
    handleKeyPress(deltaTime);
    if(hasMouseEnterWindow && first) {
      previousMousePosition.x = mousePosition.x;
      previousMousePosition.y = mousePosition.y; 
      first = false;
    }
    float dx = locked ? 0.0f : mousePosition.x - previousMousePosition.x;
    float dy = locked ? 0.0f : previousMousePosition.y - mousePosition.y;
    previousMousePosition.x = mousePosition.x;
    previousMousePosition.y = mousePosition.y;
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

  void PerspectiveCamera::scroll(const MouseScrolledEvent& mouseScrolledEvent) {
    fov += -mouseScrolledEvent.yOffset * zoomSpeed;
    fov = std::max(10.0f, fov);
    fov = std::min(fov, 90.0f);
    projection = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
  }

  void PerspectiveCamera::resize(const WindowResizedEvent& windowResizedEvent) {
    aspectRatio = static_cast<float>(windowResizedEvent.width / windowResizedEvent.height);
    projection = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
  }

  void PerspectiveCamera::updateProjection() {
    projection = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
  }
}