#include "ShaderAssets.h"

ShaderAssets::ShaderAssets() {
    allShaders = std::hash_map<unsigned int, Shader*>();
}

ShaderAssets::~ShaderAssets() {}

unsigned int ShaderAssets::LoadShader(const char* path) {
	Shader* shader = new Shader(path);
	allShaders.insert(std::pair<unsigned int, Shader*>(shader->GetID(), shader));
}

void ShaderAssets::UseShader(unsigned int shader) {
	allShaders[shader]->Bind();
}

void ShaderAssets::DeleteShader(unsigned int shader) {
	allShaders[shader]->~Shader();
}

void ShaderAssets::DeleteAllShader() {
	for (int i = 0; i < allShaders.size(); i++) {
		allShaders[i]->~Shader();
	}
}