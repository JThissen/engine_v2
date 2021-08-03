#include "layoutBuffer.hpp"

namespace engine {
  LayoutBuffer::LayoutBuffer(std::initializer_list<Layout> layout)
    : buffer(layout) {
      setOffsetAndStride();
  }

  void LayoutBuffer::setOffsetAndStride() {
    stride = 0;
    std::size_t offset = 0;
    for(int i = 0; i < buffer.size(); i++) {
      stride += buffer[i].sizeInBytes;
      buffer[i].offset = offset;
      offset += buffer[i].sizeInBytes;
    }
  }
}
