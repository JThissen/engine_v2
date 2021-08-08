#ifndef OPENGL_RENDERER_H
#define OPENGL_RENDERER_H

#include "../headers.hpp"
#include "../opengl/openglVertexArray.hpp"
#include "../renderer/shader.hpp"
#include <glm/glm.hpp>

namespace engine {
  class OpenglRenderer {
    public:
    void init();
    void setViewport(GLint x, GLint y, GLsizei width, GLsizei height);
    void setClearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
    void clear();
    void draw(
      std::shared_ptr<Shader> shader,
      const glm::mat4& modelMatrix,
      const glm::mat4& viewMatrix,
      const glm::mat4& projectionMatrix,
      std::shared_ptr<OpenglVertexArray> vertexArray
    );
  };
}

#endif