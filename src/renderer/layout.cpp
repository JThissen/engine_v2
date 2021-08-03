#include "layout.hpp"

namespace engine {
    Layout::Layout(GLSLType glslType, const std::string& name, bool normalized) 
      : name(name), normalized(normalized ? GL_TRUE : GL_FALSE) {
      parseGLSLType(glslType);
    }

  int Layout::GLSLTypeToSize(GLSLType type) {
    switch(type) {
      case GLSLType::FLOAT: return 1;
      case GLSLType::VEC2:  return 2;
      case GLSLType::VEC3:  return 3;
      case GLSLType::MAT3:  return 3;
      case GLSLType::MAT4:  return 4;
      case GLSLType::INT:   return 1;
      case GLSLType::BOOL:  return 1;
    }
    std::cout << "Could not find GLSL type." << std::endl;
    return 0;
  };

  int Layout::GLSLTypeToSizeInBytes(GLSLType type) {
    switch(type) {
      case GLSLType::FLOAT: return 1 * 4;
      case GLSLType::VEC2:  return 2 * 4;
      case GLSLType::VEC3:  return 3 * 4;
      case GLSLType::MAT3:  return 3 * 3 * 4;
      case GLSLType::MAT4:  return 4 * 4 * 4;
      case GLSLType::INT:   return 1 * 2;
      case GLSLType::BOOL:  return 1 * 1;
    }
    std::cout << "Could not find GLSL type." << std::endl;
    return 0;
  }

  GLenum Layout::GLSLTypeToGLType(GLSLType type) {
    switch(type) {
      case GLSLType::FLOAT: return GL_FLOAT;
      case GLSLType::VEC2:  return GL_FLOAT;
      case GLSLType::VEC3:  return GL_FLOAT;
      case GLSLType::MAT3:  return GL_FLOAT;
      case GLSLType::MAT4:  return GL_FLOAT;
      case GLSLType::INT:   return GL_INT;
      case GLSLType::BOOL:  return GL_BOOL;
    }
    std::cout << "Could not find GLSL type." << std::endl;
    return 0;
  };

  void Layout::parseGLSLType(GLSLType glslType) {
    this->glslType = glslType;
    size = GLSLTypeToSize(glslType);
    sizeInBytes = GLSLTypeToSizeInBytes(glslType);
    glType = GLSLTypeToGLType(glslType);
  }
}
