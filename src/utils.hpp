#ifndef UTILS_H
#define UTILS_H

#include "headers.hpp"

namespace engine {
  class Utils {
    public:
    template<typename T1, typename... T2>
    static void print(T1&& first, T2&&... rest) {
      std::cout << first;
      (..., (std::cout << ", " << rest));
      std::cout << std::endl;
    }
  };
}

#endif