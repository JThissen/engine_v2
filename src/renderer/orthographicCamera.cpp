#include "orthographicCamera.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/quaternion.hpp>
#include "../utils.hpp"

namespace engine {
  OrthographicCamera::OrthographicCamera(float windowWidth, float windowHeight, float speed, float zoomSpeed, float nearPlane, float farPlane)
    : aspectRatio(windowWidth / windowHeight), speed(speed), zoomSpeed(zoomSpeed), nearPlane(nearPlane), farPlane(farPlane) {
    view = glm::lookAt(position, position + z, y);
    projection = glm::ortho(-aspectRatio * zoom, aspectRatio * zoom, -zoom, zoom, nearPlane, farPlane);
  }

  void OrthographicCamera::handleKeyPress(DeltaTime deltaTime) {
    if(WindowInput::isKeyPressed(Key::KeyCode::A)) {
      position -= glm::normalize(glm::cross(y, z)) * speed * deltaTime.seconds();
    } else if(WindowInput::isKeyPressed(Key::KeyCode::D)) {
      position += glm::normalize(glm::cross(y, z)) * speed * deltaTime.seconds();
    }
    if(WindowInput::isKeyPressed(Key::KeyCode::S)) {
      position -= glm::normalize(glm::cross(x, y)) * speed * deltaTime.seconds();
    } else if(WindowInput::isKeyPressed(Key::KeyCode::W)) {
      position += glm::normalize(glm::cross(x, y)) * speed * deltaTime.seconds();
    }
  }

  void OrthographicCamera::updateView(DeltaTime deltaTime, const glm::vec2& mousePosition, bool hasMouseEnterWindow) {
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

  void OrthographicCamera::scroll(const MouseScrolledEvent& mouseScrolledEvent) {
    zoom -= mouseScrolledEvent.yOffset * zoomSpeed;
    zoom = zoom <= 1.0f ? 1.0f : zoom;
    projection = glm::ortho(-aspectRatio * zoom, aspectRatio * zoom, -zoom, zoom, nearPlane, farPlane);
  }

  void OrthographicCamera::resize(const WindowResizedEvent& windowResizedEvent) {
    aspectRatio = static_cast<float>(windowResizedEvent.width / windowResizedEvent.height);
    projection = glm::ortho(-aspectRatio * zoom, aspectRatio * zoom, -zoom, zoom, nearPlane, farPlane);
  }
}