#include "openglTexture.hpp"
#include "stb_image.h"

namespace engine {
  OpenglTexture::OpenglTexture(const std::string& path) {
    auto internalFormat = 0;
    auto format = 0;
    stbi_set_flip_vertically_on_load(1);
    auto data = stbi_load(path.data(), &width, &height, &channels, 0);

    if(channels == 3) {
      internalFormat = GL_RGB8;
      format = GL_RGB;
    } else if(channels == 4) {
      internalFormat = GL_RGBA8;
      format = GL_RGBA;
    }

    glCreateTextures(GL_TEXTURE_2D, 1, &textureId);
    glTextureStorage2D(textureId, 1, internalFormat, width, height);
    glTextureParameteri(textureId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(textureId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTextureParameteri(textureId, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(textureId, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTextureSubImage2D(textureId, 0, 0, 0, width, height, format, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);
  }

  OpenglTexture::~OpenglTexture() {
    glDeleteTextures(1, &textureId);
  }

  void OpenglTexture::bind(int unit) {
    glBindTextureUnit(unit, textureId);
  }
}