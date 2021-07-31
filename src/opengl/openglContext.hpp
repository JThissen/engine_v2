#ifndef OPENGL_CONTEXT_H
#define OPENGL_CONTEXT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../headers.hpp"
#include "../renderer/context.hpp"

namespace engine {
  class OpenglContext : public Context {
    private:
      GLFWwindow* glfwWindow;
    public:
      OpenglContext(GLFWwindow* glfwWindow);
      virtual void create() override;
      virtual void swapBuffers() override;
  };
}


#endif