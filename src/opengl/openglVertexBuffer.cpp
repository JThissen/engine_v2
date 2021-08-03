#include "openglVertexBuffer.hpp"

namespace engine {
  OpenglVertexBuffer::OpenglVertexBuffer(GLsizeiptr size) {
    glCreateBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
  }

  OpenglVertexBuffer::OpenglVertexBuffer(float* vertices, GLsizeiptr size, LayoutBuffer&& layoutBuffer)
    : layoutBuffer(layoutBuffer) {
    glCreateBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), vertices, GL_STATIC_DRAW);
  }

  OpenglVertexBuffer::~OpenglVertexBuffer() {
    glDeleteBuffers(1, &buffer);
  }

  void OpenglVertexBuffer::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
  }

  void OpenglVertexBuffer::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  void OpenglVertexBuffer::subData(GLsizeiptr size, const void* data) {
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
  }
}
