#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "ShaderUtil.hpp"
#include "ShaderDrawUtil.hpp"

void ShaderDrawUtil::DrawTriangle(float* positions) {
	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), positions, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

	std::string vertexShader = ShaderUtil::ReadShaderFromFile("./src/shader/TriangleVertexShader");
	std::string fragmentShader = ShaderUtil::ReadShaderFromFile("./src/shader/TriangleFragmentShader");

	unsigned int shader = ShaderUtil::CreateShader(vertexShader, fragmentShader);
	glUseProgram(shader);
}
