#ifndef OPENGL_VERTEX_ARRAY_H
#define OPENGL_VERTEX_ARRAY_H

#include <glad/glad.h>
#include "../headers.hpp"
#include "../opengl/openglVertexBuffer.hpp"
#include "../opengl/openglIndexBuffer.hpp"

namespace engine {
  class OpenglVertexArray {
    public:
    unsigned int vertexArray;
    std::vector<std::shared_ptr<OpenglVertexBuffer>> vertexBuffers;
    std::shared_ptr<OpenglIndexBuffer> indexBuffer;

    void pushVertexBuffer(std::shared_ptr<OpenglVertexBuffer> vertexBuffer);
    void setIndexBuffer(std::shared_ptr<OpenglIndexBuffer> indexBuffer);

    OpenglVertexArray();
    ~OpenglVertexArray();
    void bind();
    void unbind();
  };
}

#endif
