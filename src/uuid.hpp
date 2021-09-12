#ifndef UUID_H
#define UUID_H

#include "headers.hpp"

namespace engine {
  class UUID {
    public:
    static std::string create();
    static int createInt();
  };
}

#endif