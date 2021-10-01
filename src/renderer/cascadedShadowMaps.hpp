#ifndef CASCADED_SHADOW_MAPS_H
#define CASCADED_SHADOW_MAPS_H

#include "../headers.hpp"
#include "../opengl/openglRenderer.hpp"
#include "./perspectiveCamera.hpp"
#include "glm/glm.hpp"

// based on https://developer.download.nvidia.com/SDK/10.5/opengl/src/cascaded_shadow_maps/doc/cascaded_shadow_maps.pdf
namespace engine {
  class CascadedShadowMaps {
    private:
      unsigned int fbo;
      unsigned int textureResolution = 4096;
      unsigned int lightViewProjectionMatrixBuffer;
      std::vector<float> shadowCascadeLevels;
      std::vector<int> frustums;
      std::array<glm::vec3, 8> frustumCoordinates;
      std::shared_ptr<OpenglRenderer> openglRenderer;
      std::shared_ptr<PerspectiveCamera> camera;
      glm::vec3 light;
      glm::mat4 lightViewMatrix;
      
      glm::mat4 lightViewProjectionMatrix(float nearPlane, float farPlane, int index);
      std::vector<glm::mat4> lightViewProjectionMatrices();
    
    public:
      unsigned int depthTextures;

      CascadedShadowMaps(std::shared_ptr<OpenglRenderer> openglRenderer, std::shared_ptr<PerspectiveCamera> camera);
      void bind();
      void update();
      void unbind();
      static std::string name();
  };
}

#endif
