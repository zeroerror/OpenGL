#pragma once
#pragma once
#include <string>

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{

private:
	std::string m_FilePath;
	unsigned int m_RendererID;

public:
	Shader(const std::string& filePath);
	~Shader();

	void Bind();
	void UnBind();
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	int GetUniformLocation(const std::string& name);

private:
	ShaderProgramSource ParseShader(const std::string& filePath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

	std::string ReadShaderFromFile(const char* filepath);
	char* GetCurrentDir(size_t count);
};
