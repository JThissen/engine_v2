#ifndef LAYOUT_BUFFER
#define LAYOUT_BUFFER

#include "../headers.hpp"
#include "layout.hpp"

namespace engine {
  class LayoutBuffer {
    public:
    std::vector<Layout> buffer;
    int stride;
    LayoutBuffer() {} //temp
    LayoutBuffer(std::initializer_list<Layout> layout);
    void setOffsetAndStride();
  };
}

#endif
