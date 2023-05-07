#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "ShaderUtil.hpp"
#include "ShaderDrawUtil.hpp"
#include "ShaderTest.hpp"

int ShaderTest::DrawQuad()
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "My OpenGL Window", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
		std::cout << "ERROR" << std::endl;

	std::cout << glGetString(GL_VERSION) << std::endl;

	// Define Vertext Position
	float positions[12] = {
		-0.5f,
		-0.5f,

		0.5f,
		-0.5f,

		0.5,
		0.5f,

		-0.5f,
		0.5f,
	};

	unsigned int indices[6] = {
		0, 1, 2,
		2, 3, 0 };

	ShaderDrawUtil::DrawWithIndices(positions, 12, indices, 6);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}