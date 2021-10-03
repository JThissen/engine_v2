#ifndef BLOOM_H
#define BLOOM_H

#include "../headers.hpp"
#include "shader.hpp"
#include "shaderBuilder.hpp"
#include "geometry.hpp"
#include "glm/glm.hpp"

namespace engine {
  class Bloom {
    private:
    unsigned int quadVao;
    unsigned int quadBuffer;
    unsigned int quadTextureCoordsBuffer;
    unsigned int quadIndicesBuffer;
    int flipValue = 0;
    std::unique_ptr<Shader> quadShader;
    void createQuad();
    void drawQuad();
    void flip01();

    public:
    int width;
    int height;
    int amount = 1;
    Bloom(int width, int height);
    void gaussianBlur(unsigned int colorBufferTexture);
    unsigned int fbos[2];
    unsigned int textures[2];
    static std::string name();
  };
}

#endif