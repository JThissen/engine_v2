#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "../headers.hpp"

namespace engine {
  class Geometry {
    public:
    static std::array<float, 18> axesGeometry;
    static std::array<unsigned char, 24> axesColor;
    static std::array<float, 216> cubeGeometry;
    static std::array<unsigned char, 144> cubeColor;
    static std::array<float, 60> planeGeometry;
  };
}

#endif