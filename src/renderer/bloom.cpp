#include "bloom.hpp"
#include "../utils.hpp"
#include "geometry.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

namespace engine {
  Bloom::Bloom(int width, int height)
   : width(width), height(height) {
    glGenFramebuffers(2, &fbos[0]);
    glGenTextures(2, &textures[0]);

    for(int i = 0; i < 2; i++) {
      glBindTexture(GL_TEXTURE_2D, textures[i]);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
      glBindFramebuffer(GL_FRAMEBUFFER, fbos[i]);
      glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + 0, GL_TEXTURE_2D, textures[i], 0);
      glDrawBuffer(GL_COLOR_ATTACHMENT0);
      
      if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        throw std::runtime_error("[" + Bloom::name() + "]: Framebuffer is incomplete.");
      }
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    createQuad();
  }

  void Bloom::flip01() {
    flipValue = 1 - flipValue;
  }

  void Bloom::gaussianBlur(unsigned int colorBufferTexture) {
    bool first = true;

    if(amount == 0) {
      textures[0] = colorBufferTexture;
      first = true;
      return;
    }

    for(int i = 0; i < amount; i++) {
      glCullFace(GL_BACK);
      glBindFramebuffer(GL_FRAMEBUFFER, fbos[flipValue]);
      glViewport(0, 0, width, height);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      quadShader->useProgram();
      glm::mat4 modelMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f));
      glUniformMatrix4fv(glGetUniformLocation(quadShader->program, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
      glActiveTexture(GL_TEXTURE0);
      if(first) {
        glBindTexture(GL_TEXTURE_2D, colorBufferTexture);
        first = false;
      } else {
        glBindTexture(GL_TEXTURE_2D, textures[1 - flipValue]);
      }
      quadShader->setUniform1i(flipValue, "horizontal");
      drawQuad();
      quadShader->disuseProgram();
      flip01();
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
  }

  void Bloom::createQuad() {
    glGenBuffers(1, &quadBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, quadBuffer);
    glBufferData(GL_ARRAY_BUFFER, Geometry::planeGeometry2.size() * sizeof(float), static_cast<void*>(Geometry::planeGeometry2.data()), GL_STATIC_DRAW);
    glGenVertexArrays(1, &(quadVao));
    glBindVertexArray(quadVao);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 12, nullptr);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 12, (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 12, (void*)(sizeof(float) * 7));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 12, (void*)(sizeof(float) * 10));
    glBindVertexArray(0);

    // glGenBuffers(1, &quadBuffer);
    // glBindBuffer(GL_ARRAY_BUFFER, quadBuffer);
    // glBufferData(GL_ARRAY_BUFFER, Geometry::quadGeometry.size() * sizeof(float), static_cast<void*>(Geometry::quadGeometry.data()), GL_STATIC_DRAW);
    
    // glGenVertexArrays(1, &quadVao);
    // glBindVertexArray(quadVao);
    // glEnableVertexAttribArray(0);
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, nullptr);
    // glEnableVertexAttribArray(1);
    // glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(sizeof(float) * 3));

    // glGenBuffers(1, &quadIndicesBuffer);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadIndicesBuffer);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, Geometry::quadIndices.size() * sizeof(unsigned int), static_cast<void*>(Geometry::quadIndices.data()), GL_STATIC_DRAW);

    // glGenBuffers(1, &quadTextureCoordsBuffer);
    // glBindBuffer(GL_ARRAY_BUFFER, quadTextureCoordsBuffer);
    // glBufferData(GL_ARRAY_BUFFER, Geometry::quadTextureCoordinates.size() * sizeof(float), static_cast<void*>(Geometry::quadTextureCoordinates.data()), GL_STATIC_DRAW);
    // glEnableVertexAttribArray(1);
    // glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);

    glBindVertexArray(0);

    ShaderBuilder shaderBuilder;
    shaderBuilder.createProgram()
      .attachVertexShader("./../src/shaders/blur.vs")
      .attachFragmentShader("./../src/shaders/blur.fs")
      .linkProgram();
    quadShader = std::move(shaderBuilder.shader);
  }

  void Bloom::drawQuad() {
    glBindVertexArray(quadVao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadIndicesBuffer);
    // glDrawElements(GL_TRIANGLES, Geometry::quadIndices.size(), GL_UNSIGNED_INT, nullptr);
  }

  std::string Bloom::name() {
    return "Bloom";
  }
}