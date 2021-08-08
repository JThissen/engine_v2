#include "shader.hpp"
#include <glad/glad.h>

namespace engine {
		Shader::Shader() {
		program = glCreateProgram();
	}
	
	Shader::~Shader() {
	  glDeleteProgram(program);
	}
	
	void Shader::useProgram() {
		glUseProgram(program);
	}
	
	void Shader::disuseProgram() {
		glUseProgram(0);
	}
	
	std::string Shader::readShader(const std::string& path) {
		std::fstream fstream;
		std::vector<char> buffer;
		fstream.open(path, std::ios::in);
	
		try {
			if (fstream.is_open()) {
				fstream.seekg(0, std::ios::end);
				buffer.resize(fstream.tellg());
				fstream.seekg(0, std::ios::beg);
				fstream.read(buffer.data(), buffer.size());
				fstream.close();
			}
			else {
				std::cout << "Could not read shader. Log: " << path.data() << std::endl;
			}
		}
		catch (const std::ios_base::failure & e) {
			std::cerr << "Unable to read shader.\n Error: " << e.what() << "\nCode: " << e.code() << std::endl;
		}
		return std::string(buffer.begin(), buffer.end());
	}
	
	void Shader::attachShader(const std::string& shaderPath, ShaderType shaderType) {
		std::string shaderSource = readShader(shaderPath);
		GLuint shader;
	
	  switch (shaderType) {
			case ShaderType::VERTEX: shader = glCreateShader(GL_VERTEX_SHADER); break;
			case ShaderType::TESS_CONTROL: shader = glCreateShader(GL_TESS_CONTROL_SHADER); break;
			case ShaderType::TESS_EVAL: shader = glCreateShader(GL_TESS_EVALUATION_SHADER); break;
			case ShaderType::GEOMETRY: shader = glCreateShader(GL_GEOMETRY_SHADER); break;
			case ShaderType::FRAGMENT: shader = glCreateShader(GL_FRAGMENT_SHADER); break;
			default: std::cout << "Invalid shader type." << std::endl; return;
		}
	
		const GLchar *source = (const GLchar *)shaderSource.c_str();
	  glShaderSource(shader, 1, &source, 0);
	  glCompileShader(shader);
	  GLint isCompiled = 0;
	  glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
	
		if(isCompiled == GL_FALSE) {
	  	GLint maxLength = 0;
	    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
	    std::vector<GLchar> infoLog(maxLength);
	    glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);
	    std::cout << "Could not compile " << shaderTypeToString(shaderType) << " shader. Log: " << infoLog.data() << std::endl;
	    glDeleteShader(shader);
	    return;
	  }
	  glAttachShader(program, shader);
	  attachments.push_back(shader);
	}
	
	void Shader::linkProgram() {
		glLinkProgram(program);
	  GLint isLinked = 0;
	  glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
	
		if (isLinked == GL_FALSE) {
	  	GLint maxLength = 0;
	  	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
	  	std::vector<GLchar> infoLog(maxLength);
	  	glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
	    std::cout << "Could not link shader. Log:" << infoLog.data() << std::endl;
	  	glDeleteProgram(program);
	
			for(int i = 0; i <= attachments.size(); i++) {
				glDeleteShader(attachments[i]);
	    }
	  	return;
	  }
	
		for(int i = 0; i <= attachments.size(); i++) {
			glDetachShader(program, attachments[i]);
		}
	}
	
	std::string Shader::shaderTypeToString(ShaderType shaderType) const {
		std::unordered_map<ShaderType, std::string> enumMap = {
			{ShaderType::VERTEX, "VERTEX"},
			{ShaderType::TESS_CONTROL, "TESS_CONTROL"},
			{ShaderType::TESS_EVAL, "TESS_EVAL"},
			{ShaderType::GEOMETRY, "GEOMETRY"},
			{ShaderType::FRAGMENT, "FRAGMENT"}
		};
		auto it = enumMap.find(shaderType);
		if (it == enumMap.end()) {
	    std::cerr << "Invalid shader type." << std::endl;
	  }
		return it->second;
	}

	void Shader::setUniform4f(const glm::vec4& rgba, const std::string& name) const {
		glUniform4f(glGetUniformLocation(program, name.data()), rgba.x, rgba.y, rgba.z, rgba.z);
	}
}
