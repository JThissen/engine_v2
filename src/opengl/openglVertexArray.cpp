#include "openglVertexArray.hpp"

namespace engine {
  OpenglVertexArray::OpenglVertexArray() {
    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);
  }

    OpenglVertexArray::~OpenglVertexArray() {
    glDeleteVertexArrays(1, &vertexArray);
  }

  void OpenglVertexArray::bind() {
    glBindVertexArray(vertexArray);
  }

  void OpenglVertexArray::unbind() {
    glBindVertexArray(0);
  }

  void OpenglVertexArray::pushVertexBuffer(std::shared_ptr<OpenglVertexBuffer> vertexBuffer) {
    glBindVertexArray(vertexArray);
    vertexBuffer->bind();
    
    for(int i = 0; i < vertexBuffer->layoutBuffer.buffer.size(); i++) {
      glEnableVertexAttribArray(i);
      glVertexAttribPointer(
        i, 
        vertexBuffer->layoutBuffer.buffer[i].size, 
        vertexBuffer->layoutBuffer.buffer[i].glType, 
        vertexBuffer->layoutBuffer.buffer[i].normalized, 
        vertexBuffer->layoutBuffer.stride, //in bytes
        reinterpret_cast<const void*>(vertexBuffer->layoutBuffer.buffer[i].offset) //in bytes
      );
    }
    vertexBuffers.push_back(vertexBuffer);
  }

  void OpenglVertexArray::setIndexBuffer(std::shared_ptr<OpenglIndexBuffer> indexBuffer) {
    glBindVertexArray(vertexArray);
    indexBuffer->bind();
    this->indexBuffer = indexBuffer;
  }
}
