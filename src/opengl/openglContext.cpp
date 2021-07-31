#include "openglContext.hpp"

namespace engine {
  OpenglContext::OpenglContext(GLFWwindow* glfwWindow) : glfwWindow(glfwWindow) {
    
  }

  void OpenglContext::create() {
    glfwMakeContextCurrent(glfwWindow);
    int isGLLoaded = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));

    if(!isGLLoaded) {
      std::cout << "Could not load OpenGL functions." << std::endl;
      glfwTerminate();
      return;
    }

    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "Shadling language version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
  }

  void OpenglContext::swapBuffers() {
    glfwSwapBuffers(glfwWindow);
  }
}
