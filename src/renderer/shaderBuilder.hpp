#ifndef SHADER_BUILDER_H
#define SHADER_BUILDER_H

#include "shader.hpp"

class ShaderBuilder {
  public:
  	std::unique_ptr<Shader> shader;
  	ShaderBuilder& createProgram();
  	ShaderBuilder& attachVertexShader(const std::string& shaderPath);
  	ShaderBuilder& attachTessControlShader(const std::string& shaderPath);
  	ShaderBuilder& attachTessEvalShader(const std::string& shaderPath);
  	ShaderBuilder& attachGeometryShader(const std::string& shaderPath);
  	ShaderBuilder& attachFragmentShader(const std::string& shaderPath);
  	void linkProgram();
};

#endif