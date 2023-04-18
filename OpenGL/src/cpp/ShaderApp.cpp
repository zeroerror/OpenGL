#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "ShaderUtil.hpp"
#include "ShaderDrawUtil.hpp"

int main(void)
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
	static float positions[12] = {
	-0.5f,
	-0.5f,
	0.5f,
	-0.5f,
	0,
	0.5f,
	-1.0f,
	0.5f,
	1.0f,
	0.5f,
	0.5f,
	};

	ShaderDrawUtil::DrawTriangle(positions);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawArrays(GL_TRIANGLES, 3, 3);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}