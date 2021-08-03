#ifndef LAYOUT
#define LAYOUT

#include <glad/glad.h>
#include "../headers.hpp"

namespace engine {
  enum class GLSLType { FLOAT, VEC2, VEC3, MAT3, MAT4, INT, BOOL };

  class Layout {
    public:
    std::string name;
    int size;
    int sizeInBytes;
    GLSLType glslType;
    GLenum glType;
    GLboolean normalized;
    std::size_t offset;

    Layout(GLSLType glslType, const std::string& name, bool normalized = false);
    
    private:
    void parseGLSLType(GLSLType glslType);
    static int GLSLTypeToSize(GLSLType type);
    static int GLSLTypeToSizeInBytes(GLSLType type);
    static GLenum GLSLTypeToGLType(GLSLType type);
  };
}

#endif
