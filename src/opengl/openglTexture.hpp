#ifndef OPENGL_TEXTURE_H
#define OPENGL_TEXTURE_H

#include "../headers.hpp"
#include <glad/glad.h>

namespace engine {
  class OpenglTexture {
    public:
    int width;
    int height;
    int channels;
    GLuint textureId;
    OpenglTexture(const std::string& path);
    ~OpenglTexture();
    void bind(int unit);
  };
}

#endif