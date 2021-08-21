#ifndef ORTHOGRAPHIC_CAMERA_CONTROLLER_H
#define ORTHOGRAPHIC_CAMERA_CONTROLLER_H

#include "orthographicCamera.hpp"
#include "../headers.hpp"
#include "../deltaTime.hpp"
#include "../mouseEvent.hpp"
#include "../windowEvent.hpp"
#include "glm/glm.hpp"

namespace engine {
  class OrthographicCameraController {
    public:
    std::unique_ptr<OrthographicCamera> orthographicCamera;
    float translateSpeed = 1.0f;
    float zoom = 1.0f;
    float zoomSpeed = 0.5f;
    float aspectRatio;

    OrthographicCameraController(float aspectRatio, float translateSpeed = 1.0f, float zoomSpeed = 0.5f);
    void mouseScroll(const MouseScrolledEvent& mouseScrolledEvent);
    void resize(const WindowResizedEvent& windowResizedEvent);
    void update(DeltaTime deltaTime);
  };
}

#endif
