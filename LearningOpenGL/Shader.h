#pragma once
#include <string>
#include <unordered_map>;
#include "vendor/glm/glm/glm.hpp"

class Shader {
private:
	unsigned int m_ShaderID;
	std::unordered_map<std::string, int> m_LocationCache;
public:
	Shader(const char* vertexSource, const char* fragmentSource);
	~Shader();
	void SetUniform4f(const std::string& name, float v1, float v2, float v3, float v4);
	void SetUniformi(const std::string& name, int value);
	void SetUniformMat4f(const std::string& name, const glm::mat4& mat);
	void Bind() const;
	void Unbind() const;

private:
	int getUniformLocation(const std::string& name);
};