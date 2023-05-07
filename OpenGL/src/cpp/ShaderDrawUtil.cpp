#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "ShaderUtil.hpp"
#include "ShaderDrawUtil.hpp"

unsigned int ShaderDrawUtil::Draw(float *positions, unsigned int posLen, unsigned int *indices, unsigned int indLen)
{
	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, posLen * sizeof(float), positions, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

	unsigned int ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indLen * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	std::string vertexShader = ShaderUtil::ReadShaderFromFile("./src/shader/TriangleVertexShader");
	std::string fragmentShader = ShaderUtil::ReadShaderFromFile("./src/shader/TriangleFragmentShader");

	unsigned int shader = ShaderUtil::CreateShader(vertexShader, fragmentShader);
	glUseProgram(shader);

	return shader;
}
