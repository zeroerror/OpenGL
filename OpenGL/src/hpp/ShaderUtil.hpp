#pragma once
#include <string>

namespace ShaderUtil {

	std::string ReadShaderFromFile(const char* filepath);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

}
