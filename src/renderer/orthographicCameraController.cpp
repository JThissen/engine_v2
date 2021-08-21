#include "orthographicCameraController.hpp"
#include "../windowInput.hpp"
#include "../key.hpp"
#include "../utils.hpp"

namespace engine {
  OrthographicCameraController::OrthographicCameraController(float aspectRatio, float translateSpeed, float zoomSpeed) 
    : aspectRatio(aspectRatio), translateSpeed(translateSpeed), zoomSpeed(zoomSpeed) {
    orthographicCamera = std::make_unique<OrthographicCamera>(-aspectRatio * zoom, aspectRatio * zoom, -zoom, zoom);
  }

  void OrthographicCameraController::update(DeltaTime deltaTime) {
    if(WindowInput::isKeyPressed(Key::KeyCode::A)) {
      orthographicCamera->position.x -= translateSpeed * deltaTime.seconds();
    } else if(WindowInput::isKeyPressed(Key::KeyCode::D)) {
      orthographicCamera->position.x += translateSpeed * deltaTime.seconds();
    }
    if(WindowInput::isKeyPressed(Key::KeyCode::S)) {
      orthographicCamera->position.y -= translateSpeed * deltaTime.seconds();
    } else if(WindowInput::isKeyPressed(Key::KeyCode::W)) {
      orthographicCamera->position.y += translateSpeed * deltaTime.seconds();
    }
    orthographicCamera->calculateViewMatrix();
  }

  void OrthographicCameraController::mouseScroll(const MouseScrolledEvent& mouseScrolledEvent) {
    zoom -= mouseScrolledEvent.yOffset * zoomSpeed;
    Utils::print(-aspectRatio * zoom, aspectRatio * zoom, -zoom, zoom);
    orthographicCamera->setProjectionMatrix(-aspectRatio * zoom, aspectRatio * zoom, -zoom, zoom);
  }

  void OrthographicCameraController::resize(const WindowResizedEvent& windowResizedEvent) {
    aspectRatio = static_cast<float>(windowResizedEvent.width / windowResizedEvent.height);
    orthographicCamera->setProjectionMatrix(-aspectRatio * zoom, aspectRatio * zoom, -zoom, zoom);
  }
}
