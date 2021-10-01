#include "cascadedShadowMaps.hpp"
#include "../utils.hpp"

#include <glad/glad.h>

namespace engine {
  CascadedShadowMaps::CascadedShadowMaps(std::shared_ptr<OpenglRenderer> openglRenderer, std::shared_ptr<PerspectiveCamera> camera)
   : openglRenderer(openglRenderer), camera(camera) {
    shadowCascadeLevels = { 
      camera->farPlane / 50.0f, 
      camera->farPlane / 25.0f, 
      camera->farPlane / 10.0f, 
      camera->farPlane / 2.0f 
    };

    glGenTextures(1, &depthTextures);
    glBindTexture(GL_TEXTURE_2D_ARRAY, depthTextures);
    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_DEPTH_COMPONENT32F, textureResolution, textureResolution, static_cast<int>(shadowCascadeLevels.size()) + 1, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    constexpr float params[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glTexParameterfv(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BORDER_COLOR, params);
    
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTextures, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    int fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if(fboStatus != GL_FRAMEBUFFER_COMPLETE) {
      throw std::runtime_error("[" + CascadedShadowMaps::name() + "]: Framebuffer is incomplete.");
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glGenBuffers(1, &lightViewProjectionMatrixBuffer);
    glBindBuffer(GL_UNIFORM_BUFFER, lightViewProjectionMatrixBuffer);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4x4) * 16, nullptr, GL_STATIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, lightViewProjectionMatrixBuffer);
  }

  void CascadedShadowMaps::bind() {
    openglRenderer->depthPass = true;
    update();
    std::vector<glm::mat4> matrices = lightViewProjectionMatrices();
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_TEXTURE_2D_ARRAY, depthTextures, 0);
    glViewport(0, 0, textureResolution, textureResolution);
    openglRenderer->clear();
    glCullFace(GL_FRONT);
    glBindBuffer(GL_UNIFORM_BUFFER, lightViewProjectionMatrixBuffer);
    for(int i = 0; i < matrices.size(); i++) {
      glBufferSubData(GL_UNIFORM_BUFFER, i * sizeof(glm::mat4x4), sizeof(glm::mat4x4), &matrices[i]);
    }
  }

  void CascadedShadowMaps::update() {
    shadowCascadeLevels = { 
      camera->farPlane / 50.0f, 
      camera->farPlane / 25.0f, 
      camera->farPlane / 10.0f, 
      camera->farPlane / 2.0f 
    };
    openglRenderer->shadowCascadeLevels = shadowCascadeLevels;
  }

  void CascadedShadowMaps::unbind() {
    glCullFace(GL_BACK);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
  }

  std::string CascadedShadowMaps::name() {
    return "CascadedShadowMaps";
  }

  std::vector<glm::mat4> CascadedShadowMaps::lightViewProjectionMatrices() {
    std::vector<glm::mat4> matrices;
    for (int i = 0; i < shadowCascadeLevels.size() + 1; i++) {
      if (i == 0) {
          matrices.push_back(lightViewProjectionMatrix(camera->nearPlane, shadowCascadeLevels[i], i));
      } else if (i < shadowCascadeLevels.size()) {
          matrices.push_back(lightViewProjectionMatrix(shadowCascadeLevels[i - 1], shadowCascadeLevels[i], i));
      } else {
          matrices.push_back(lightViewProjectionMatrix(shadowCascadeLevels[i - 1], camera->farPlane, i));
      }
    }
    return matrices;
  }

  glm::mat4 CascadedShadowMaps::lightViewProjectionMatrix(float nearPlane, float farPlane, int index) {
    std::array<glm::vec3, 8> frustumCoordinates = camera->calculateFrustumCoordinates(nearPlane, farPlane);
    
    if(frustums.size() < shadowCascadeLevels.size()) {
      int frustumId = openglRenderer->createFrustum(glm::mat4(1.0f), frustumCoordinates, frustums.size());
      frustums.push_back(frustumId);
    } else {
      for(int i = 0; i < openglRenderer->objects.size(); i++) {
        if(openglRenderer->objects[i]->getObjectType() == engine::ObjectType::FRUSTUM) {
          engine::Frustum* frustum = dynamic_cast<engine::Frustum*>(openglRenderer->objects[i].get());
          if(frustum->id == frustums[index]) {
            frustum->frustumCoordinates = frustumCoordinates;
          }
        }
      }
    }

    glm::vec3 frustumCenter = glm::vec3(0.0f);
    for(const auto& fc : frustumCoordinates) {
      frustumCenter += fc;
    }
    frustumCenter /= frustumCoordinates.size();

    auto firstLight = std::find_if(openglRenderer->objects.begin(), openglRenderer->objects.end(), [](std::unique_ptr<engine::Object>& object) {
      return object->getObjectType() == engine::ObjectType::LIGHT;
    });

    light = glm::normalize(glm::vec3(
      (*firstLight)->transformData.modelMatrix[3][0],
      (*firstLight)->transformData.modelMatrix[3][1],
      (*firstLight)->transformData.modelMatrix[3][2]
    ));
    lightViewMatrix = glm::lookAt(frustumCenter + light, frustumCenter, glm::vec3(0.0f, 1.0f, 0.0f));
    float xMin = std::numeric_limits<float>::max();
    float xMax = std::numeric_limits<float>::min();
    float yMin = std::numeric_limits<float>::max();
    float yMax = std::numeric_limits<float>::min();
    float zMin = std::numeric_limits<float>::max();
    float zMax = std::numeric_limits<float>::min();

    for (auto& v : frustumCoordinates) {
      const auto frustumCoordViewSpace = lightViewMatrix * glm::vec4(v, 1.0);
      xMin = std::min(xMin, frustumCoordViewSpace.x);
      xMax = std::max(xMax, frustumCoordViewSpace.x);
      yMin = std::min(yMin, frustumCoordViewSpace.y);
      yMax = std::max(yMax, frustumCoordViewSpace.y);
      zMin = std::min(zMin, frustumCoordViewSpace.z);
      zMax = std::max(zMax, frustumCoordViewSpace.z);
    }

    // Modify z of AABB box based on scene 
    constexpr float modifier = 2.0f;
    zMin = zMin < 0 ? zMin * modifier : zMin / modifier;
    zMax = zMax < 0 ? zMax / modifier : zMax * modifier;

    // scale and translate matrix to origin (becomes ndc space [-1, 1])
    const glm::mat4 ortho = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, zMin, zMax);
    const float xScale = 2.0f / (xMax - xMin);
    const float yScale = 2.0f / (yMax - yMin);
    const float xTranslate = -0.5f * (xMin + xMax) * xScale;
    const float yTranslate = -0.5f * (yMin + yMax) * yScale;

    glm::mat4 scaleMatrixToOrigin = glm::mat4(1.0f);
    scaleMatrixToOrigin[0][0] = xScale;
    scaleMatrixToOrigin[1][1] = yScale;
    scaleMatrixToOrigin[3][0] = xTranslate;
    scaleMatrixToOrigin[3][1] = yTranslate;

    return scaleMatrixToOrigin * ortho * lightViewMatrix;
  }
}