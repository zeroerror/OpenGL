#pragma once
#include <hash_map>
#include <Shader.h>

class ShaderAssets {

public:
	ShaderAssets() {}
	~ShaderAssets() {}

	unsigned int LoadShader(const char* path);
	void UseShader(unsigned int shader);
	void DeleteShader(unsigned int shader);
	void DeleteAllShader();

private:
	std::hash_map<unsigned int, Shader*> allShaders;

};

