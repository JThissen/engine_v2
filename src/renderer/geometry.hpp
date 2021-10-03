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
    static std::array<float, 72> planeGeometry2;
    static std::array<float, 30> quadGeometry;
    static std::array<float, 12> quadTextureCoordinates;
    static std::array<unsigned int, 6> quadIndices;
  };
}

#endif