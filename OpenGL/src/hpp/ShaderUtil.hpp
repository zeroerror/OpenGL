#pragma once
#include <string>

std::string ReadShaderFromFile(const char *filepath);
unsigned int CreateShader(const std::string &vertexShader, const std::string &fragmentShader);
