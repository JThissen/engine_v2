#include "shaderBuilder.hpp"

ShaderBuilder& ShaderBuilder::createProgram() {
	shader = std::make_unique<Shader>();
	return *this;
}

ShaderBuilder& ShaderBuilder::attachVertexShader(const std::string& shaderPath) {
	shader->attachShader(shaderPath, Shader::ShaderType::VERTEX);
	return *this;
}

ShaderBuilder& ShaderBuilder::attachTessControlShader(const std::string& shaderPath) {
	shader->attachShader(shaderPath, Shader::ShaderType::TESS_CONTROL);
	return *this;
}

ShaderBuilder& ShaderBuilder::attachTessEvalShader(const std::string& shaderPath) {
	shader->attachShader(shaderPath, Shader::ShaderType::TESS_EVAL);
	return *this;
}

ShaderBuilder& ShaderBuilder::attachGeometryShader(const std::string& shaderPath) {
	shader->attachShader(shaderPath, Shader::ShaderType::GEOMETRY);
	return *this;
}

ShaderBuilder& ShaderBuilder::attachFragmentShader(const std::string& shaderPath) {
	shader->attachShader(shaderPath, Shader::ShaderType::FRAGMENT);
	return *this;
}

void ShaderBuilder::linkProgram() {
	shader->linkProgram();
}
