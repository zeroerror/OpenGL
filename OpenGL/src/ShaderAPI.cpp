#include "ShaderAPI.h"

int ShaderAPI::Draw_Quad_DynamicColor() {
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "My OpenGL Window", NULL, NULL);
	if (!window) {
		GLCall(glfwTerminate());
		return -1;
	}

	/* Make the window's context current */
	GLCall(glfwMakeContextCurrent(window));

	// Enable VSync
	GLCall(glfwSwapInterval(1));

	if (glewInit() != GLEW_OK)
		std::cout << "ERROR" << std::endl;

	std::cout << glGetString(GL_VERSION) << std::endl;

	{
		// Define Vertext Position
		float positions[] = {
			-0.5f,-0.5f,0.0f,0.0f,
			0.5f,-0.5f,1.0f,0.0f,
			0.5,0.5f,1.0f,1.0f,
			-0.5f,0.5f,0.0f,1.0f
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0 };

		// Vertex Array
		VertexArray va;
		VertexBuffer vb(positions, 4 * 4 * sizeof(float));
		VertexBufferLayout layout;

		layout.Push<float>(2);
		layout.Push<float>(2);
		va.AddBuffer(vb, layout);

		// Index Buffer
		IndexBuffer ib(indices, 6);

		// Shader
		Shader shader("res/shader/Basic.shader");
		shader.Bind();

		glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);
		shader.SetUniformMat4f("u_MVP", proj);

		shader.SetUniform1i("u_Texture", 0);

		// Texture 
		Texture texture("res/textures/room.png");
		texture.Bind();
		;
		float r = 0.0f;
		float increment = 0.1f;

		Renderer renderer;


		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window)) {
			/* Render here */

			renderer.Clear();

			shader.Bind();
			shader.SetUniform4f("u_BlendColor", r, 0.0f, 0.0f, 0.5f);
			renderer.Draw(va, ib, shader);

			// Dynamic change color
			if (r > 1.0f)
				increment = -0.05f;
			else if (r < 0.0f)
				increment = 0.05f;
			r += increment;

			/* Swap front and back buffers */
			GLCall(glfwSwapBuffers(window));

			/* Poll for and process events */
			GLCall(glfwPollEvents());
		}

	}

	glfwTerminate();
	return 0;
}
