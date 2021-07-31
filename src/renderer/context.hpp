#ifndef CONTEXT_H
#define CONTEXT_H

#include "../headers.hpp"

namespace engine {
  class Context {
    public:
      virtual ~Context() = default;
      virtual void create() = 0;
      virtual void swapBuffers() = 0;
  };
}

#endif
