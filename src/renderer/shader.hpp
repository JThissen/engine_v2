#ifndef SHADER_H
#define SHADER_H

#include "../headers.hpp"
#include <glm/glm.hpp>
#include <glad/glad.h>

namespace engine {
	class Shader {
  public:
		unsigned int program;
		std::vector<unsigned int>	attachments;
		std::string shaderName;
		enum class ShaderType { VERTEX, TESS_CONTROL, TESS_EVAL, GEOMETRY, FRAGMENT };
		Shader();
  	~Shader();
		std::string readShader(const std::string& shader_path);
		void attachShader(const std::string& shaderPath, ShaderType shaderType);
		void linkProgram();
		void useProgram();
		void disuseProgram();
		std::string shaderTypeToString(ShaderType shader_type) const;
		void setUniform4fv(const glm::vec4& rgba, const std::string& name) const;
		void setUniform3fv(const glm::vec3& rgb, const std::string& name) const;
		void setUniform1i(int value, const std::string& name) const;
		void setUniform1f(float value, const std::string& name) const;
		static void createSSBOBlock(unsigned int& SSBOBufferId, unsigned int bindingIndex, unsigned int size, void* data, unsigned int usage = GL_DYNAMIC_DRAW);
		static void updateSSBOBlock(unsigned int& SSBOBufferId, unsigned int size, void* data, unsigned int usage = GL_DYNAMIC_DRAW);
		static void setSSBOBlockSubData(unsigned int& SSBOBufferId, unsigned int offset, void* data, unsigned int size);
	};
}

#endif