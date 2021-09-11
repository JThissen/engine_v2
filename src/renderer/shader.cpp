#include "shader.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "../utils.hpp"

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
		std::ifstream file(path);
    if (!file) {
			Utils::print("Could not read shader at path", path);
			return std::string();
		}
    file.ignore(std::numeric_limits<std::streamsize>::max());
    auto size = file.gcount();
    file.clear();
    file.seekg(0, std::ios_base::beg);
    std::stringstream sstr;
    sstr << file.rdbuf();
    file.close();
    return sstr.str();
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
	  glShaderSource(shader, 1, &source, nullptr);
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

	void Shader::setUniform4fv(const glm::vec4& rgba, const std::string& name) const {
		glUniform4fv(glGetUniformLocation(program, name.data()), 1, glm::value_ptr(rgba));
	}

	void Shader::setUniform3fv(const glm::vec3& rgb, const std::string& name) const {
		glUniform3fv(glGetUniformLocation(program, name.data()), 1, glm::value_ptr(rgb));
	}

	void Shader::setUniform1i(int value, const std::string& name) const {
		glUniform1i(glGetUniformLocation(program, name.data()), value);
	}

	void Shader::setUniform1f(float value, const std::string& name) const {
		glUniform1f(glGetUniformLocation(program, name.data()), value);
	}

	void Shader::createSSBOBlock(unsigned int key, unsigned int size, void* data, unsigned int usage) {
		Utils::print("creating ssboblock with key", key);
		unsigned int bufferId;
		glGenBuffers(1, &bufferId);
		ssboCubes = std::make_pair(bufferId, size);
		updateSSBOBlock(key, size, data, usage);
		Utils::print("glbindbufferbase key", key);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, key, bufferId);
		Utils::print("created bufferid is", bufferId);
		ssboCubes = std::make_pair(bufferId, size);
		Utils::print("created ssboCubes first is", ssboCubes.first);
	}

	void Shader::updateSSBOBlock(unsigned int key, unsigned int size, void* data, unsigned int usage) {
		Utils::print("update ssbo block with key", key);
		Utils::print("size", size);
		Utils::print("ssbocubes", ssboCubes.first);
		unsigned int bufferId = ssboCubes.first;
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, bufferId);
		glBufferData(GL_SHADER_STORAGE_BUFFER, size, data, usage);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
	}
	void Shader::setSSBOBlockSubData(unsigned int key, unsigned int offset, void* data, unsigned int size) {
		unsigned int bufferId = ssboCubes.first;
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, bufferId);
		glBufferSubData(GL_SHADER_STORAGE_BUFFER, offset, size, data);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
	}
}
