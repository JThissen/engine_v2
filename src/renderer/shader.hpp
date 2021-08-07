#ifndef SHADER_H
#define SHADER_H

#include "../headers.hpp"

namespace engine {
	class Shader {
  public:
		unsigned int program;
		std::vector<unsigned int>	attachments;
		enum class ShaderType { VERTEX, TESS_CONTROL, TESS_EVAL, GEOMETRY, FRAGMENT };
		Shader();
  	~Shader();
		std::string readShader(const std::string& shader_path);
		void attachShader(const std::string& shaderPath, ShaderType shaderType);
		void linkProgram();
		void useProgram();
		void disuseProgram();
		std::string shaderTypeToString(ShaderType shader_type) const;
	};
}

#endif