#ifndef OPENGL_VERTEX_BUFFER_H
#define OPENGL_VERTEX_BUFFER_H

#include <glad/glad.h>
#include "../headers.hpp"
#include "../renderer/layoutBuffer.hpp"

namespace engine {
  class OpenglVertexBuffer {
    public:
    unsigned int buffer;
    LayoutBuffer layoutBuffer;
    OpenglVertexBuffer(GLsizeiptr size);
    OpenglVertexBuffer(float* vertices, GLsizeiptr size, LayoutBuffer&& layoutBuffer);
    ~OpenglVertexBuffer();
    void bind();
    void unbind();
    void subData(GLsizeiptr size, const void* data);
  };
}

#endif
