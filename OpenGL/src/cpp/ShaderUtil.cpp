#if defined(_WIN32)
#include <windows.h>
#else
#include <unistd.h>
#endif

#include <stdio.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>
#include "ShaderUtil.hpp"


char* GetCurrentDir(size_t size)
{
	char* buf = new char[size];
#if defined(_WIN32)
	GetCurrentDirectoryA(size, buf);
#else
	getcwd(buf, size);
#endif
	return buf;
}

std::string ReadShaderFromFile(const char* filepath)
{
	std::string fullpath;
	if (filepath[0] == '.' && filepath[1] == '/')
	{
		char* cwd = GetCurrentDir(1024);
		fullpath = std::string(cwd) + std::string("/") + std::string(filepath + 2);
		delete[] cwd;
	}
	else
	{
		fullpath = filepath;
	}

	std::ifstream stream(fullpath);
	if (!stream.is_open())
	{
		std::cout << "Can't Not Open File: " << fullpath << std::endl;
		return "";
	}

	std::stringstream buffer;
	buffer << stream.rdbuf();

	return buffer.str();
}

unsigned int CompileShader(const int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	// Error handling
	int status;
	glGetShaderiv(id, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		int len;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
		char* msg = (char*)alloca(len * sizeof(char));
		glGetShaderInfoLog(id, len, &len, msg);
		std::cout << "Compile Error=> " << (type == GL_VERTEX_SHADER ? "VertexShader" : "FragmentShder")
			<< std::endl;
		std::cout << msg << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}