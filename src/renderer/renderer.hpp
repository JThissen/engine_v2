#ifndef RENDERER_H
#define RENDERER_H

#include "../headers.hpp"
#include "../opengl/openglRenderer.hpp"

namespace engine {
  class Renderer {
    public:
    void init(); //call glenable glfunc etc.
    void destroy(); // delete vertices etc.
    void initScene();
    void destroyScene();
    void draw();

    std::unique_ptr<OpenglRenderer> openglRenderer;
  };
}

#endif
