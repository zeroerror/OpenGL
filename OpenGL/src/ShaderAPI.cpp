#include "ShaderAPI.h"

int ShaderAPI::DrawTest() {
	GLFWwindow* window;
	const char* glsl_version = "#version 330 core";

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	const unsigned int screen_width = 640;
	const unsigned int screen_height = 480;
	window = glfwCreateWindow(screen_width, screen_height, "My OpenGL Window", NULL, NULL);
	if (!window) {
		GLCall(glfwTerminate());
		return -1;
	}

	// GLFW Context
	GLCall(glfwMakeContextCurrent(window));

	// Enable VSync
	GLCall(glfwSwapInterval(1));

	if (glewInit() != GLEW_OK)
		std::cout << "ERROR" << std::endl;

	std::cout << glGetString(GL_VERSION) << std::endl;

	{
		// Define Vertext Position
		unsigned int width = 640;
		unsigned int height = 480;
		int anchorX = width / 2.0f;
		int anchorY = height / 2.0f;
		float positions[] = {
			-anchorX,-anchorY,0,0,
			width - anchorX,-anchorY,1,0,
			width - anchorX,height - anchorY ,1,1,
			-anchorX,height - anchorY,0,1,
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

		// Texture 
		Texture texture("res/textures/room.png");
		texture.Bind();

		// Args
		glm::vec3 translationA = glm::vec3(0, 0, 0);
		glm::vec3 translationB = glm::vec3(0, 0, 0);
		bool showUI = true;

		Renderer renderer;

		// IMGUI Context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init();

		test::TestClearColor colorTest;

		while (!glfwWindowShouldClose(window)) {
			GLCall(glfwPollEvents());
			renderer.Clear();

			colorTest.OnUpdate(0);
			colorTest.OnRenderer();
			//renderer.Draw(va, ib, shader);

			ImGui_ImplGlfw_NewFrame();
			ImGui_ImplOpenGL3_NewFrame();
			ImGui::NewFrame();
			colorTest.OnImGuiRender();
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			/* Swap front and back buffers */
			GLCall(glfwSwapBuffers(window));
		}

	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
