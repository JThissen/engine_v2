#include "openglIndexBuffer.hpp"

namespace engine {
  OpenglIndexBuffer::OpenglIndexBuffer(GLsizeiptr size) {
    glCreateBuffers(1, &buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
  }

  OpenglIndexBuffer::OpenglIndexBuffer(int* indices, GLsizeiptr size) {
    glCreateBuffers(1, &buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(float), indices, GL_STATIC_DRAW);
  }

  OpenglIndexBuffer::~OpenglIndexBuffer() {
    glDeleteBuffers(1, &buffer);
  }

  void OpenglIndexBuffer::bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
  }

  void OpenglIndexBuffer::unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }

  void OpenglIndexBuffer::subData(GLsizeiptr size, const void* data) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, size, data);
  }
}
