#pragma once

#include <string>

#include "glm/glm.hpp"

struct ShaderProgramSource {
	std::string VertexShader;
	std::string FragmentShader;
};

class Shader
{
public:
	Shader() = default;
	Shader(const std::string& filePath);
	~Shader();

	void SetUniform1i(const std::string& name, int value);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

	void Bind() const;
	void Unbind() const;

	ShaderProgramSource ParseShader();
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

	int GetUniformLocation(const std::string& uniform);

	void Delete();
private:
	std::string m_filePath;
	unsigned int m_shader;
};

