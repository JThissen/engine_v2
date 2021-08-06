#ifndef ORTHOGRAPHIC_CAMERA_H
#define ORTHOGRAPHIC_CAMERA_H

#include "../headers.hpp"
#include "glm/glm.hpp"

namespace engine {
  class OrthographicCamera {
    public:
    OrthographicCamera(float left, float right, float bottom, float top);
    void setProjectionMatrix(float left, float right, float bottom, float top);
    void calculateViewMatrix();
    void setPosition(const glm::vec3 position);
    void setRotation(float rotationInDegrees);

    glm::mat4 projectionMatrix = glm::mat4(1.0f);
    glm::mat4 viewMatrix = glm::mat4(1.0f);

    private:
    glm::vec3 position = glm::vec3(0.0f);
    float rotationInDegrees = 0.0f;
  };
}

#endif
