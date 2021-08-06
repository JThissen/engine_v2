#ifndef OPENGL_INDEX_BUFFER_H
#define OPENGL_INDEX_BUFFER_H

#include <glad/glad.h>
#include "../headers.hpp"

namespace engine {
  class OpenglIndexBuffer {
    public:
    unsigned int buffer;
    GLsizeiptr size;
    
    OpenglIndexBuffer(GLsizeiptr size);
    OpenglIndexBuffer(int* indices, GLsizeiptr size);
    ~OpenglIndexBuffer();
    void bind();
    void unbind();
    void subData(GLsizeiptr size, const void* data);
  };
}

#endif
