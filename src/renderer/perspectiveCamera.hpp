#ifndef PERSPECTIVE_CAMERA_H
#define PERSPECTIVE_CAMERA_H

#include "../headers.hpp"
#include "../windowInput.hpp"
#include "../deltaTime.hpp"
#include "../mouseEvent.hpp"
#include "../windowEvent.hpp"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace engine {
  class PerspectiveCamera {
    public:
    float yaw = -30.0f;
    float pitch = -30.0f;
    float speed = 5.0f;
    float fov = 45.0f;
    float sensitivity = 0.2f;
    float zoomSpeed = 5.0f;
    float nearPlane = 0.1f;
    float farPlane = 1000.0f;
    bool locked = false;
    glm::vec3 position = { -5.0f, -4.0f, -7.0f };
    glm::vec3 x = { 1.0f, 0.0f, 0.0f };
    glm::vec3 y = { 0.0f, 1.0f, 0.0f };
    glm::vec3 z = { 0.0f, 0.0f, -1.0f };
    glm::mat4 view;
    glm::mat4 projection;

    PerspectiveCamera(float windowWidth = 800.0f, float windowHeight = 600.0f, float speed = 5.0f, float fov = 45.0f, float sensitivity = 0.2f, float zoomSpeed = 5.0f, float nearPlane = 0.1f, float farPlane = 1000.0f);
    void handleKeyPress(DeltaTime deltaTime);
    void updateView(DeltaTime deltaTime, const glm::vec2& mousePosition, bool hasMouseEnterWindow);
    void scroll(const MouseScrolledEvent& mouseScrolledEvent);
    void resize(const WindowResizedEvent& windowResizedEvent);
    void updateProjection();

    private:
    bool first = true;
    float aspectRatio;
    glm::vec2 previousMousePosition = { 800.0f, 450.0f };
  };
}

#endif