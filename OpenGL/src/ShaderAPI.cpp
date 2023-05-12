#include "ShaderAPI.h"
#include "imgui/imgui.h"
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

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
	const unsigned int screen_width = 1920;
	const unsigned int screen_height = 1080;
	window = glfwCreateWindow(screen_width, screen_height, "My OpenGL Window", NULL, NULL);
	if (!window) {
		GLCall(glfwTerminate());
		return -1;
	}

	// GLFW Context
	GLCall(glfwMakeContextCurrent(window));

	// Dear IMGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
	io.IniFilename = nullptr;
	bool show_demo_window = true;

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
		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window)) {
			renderer.Clear();

			GLCall(glfwPollEvents());

			// Shader 
			shader.Bind();
			shader.SetUniform1i("u_Texture", 0);

			// - MVP 
			{
				glm::mat4 model = glm::translate(glm::mat4(1), translationA);
				glm::mat4 view = glm::translate(
					glm::mat4(glm::vec4(1, 0, 0, 0), glm::vec4(0, 1, 0, 0), glm::vec4(0, 0, 1, 0), glm::vec4(1, 1, 1, 1)), //  Equals glm::mat4(1)
					glm::vec3(0, 0, 0)
				);
				glm::mat4 proj = glm::ortho(0.0f, screen_width * 1.0f, 0.0f, screen_height * 1.0f, -1.0f, 1.0f);
				glm::mat4 mvp = proj * view * model;
				shader.SetUniformMat4f("u_MVP", mvp);
				renderer.Draw(va, ib, shader);
			}
			{
				glm::mat4 model = glm::translate(glm::mat4(1), translationB);
				glm::mat4 view = glm::translate(
					glm::mat4(glm::vec4(1, 0, 0, 0), glm::vec4(0, 1, 0, 0), glm::vec4(0, 0, 1, 0), glm::vec4(1, 1, 1, 1)), //  Equals glm::mat4(1)
					glm::vec3(0, 0, 0)
				);
				glm::mat4 proj = glm::ortho(0.0f, screen_width * 1.0f, 0.0f, screen_height * 1.0f, -1.0f, 1.0f);
				glm::mat4 mvp = proj * view * model;
				shader.SetUniformMat4f("u_MVP", mvp);
				renderer.Draw(va, ib, shader);
			}


			// Dear IMGUI frame
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
			ImGui::SliderFloat3("translationA", &translationA.x, 0, screen_width - width);
			ImGui::SliderFloat3("translationB", &translationB.x, 0, screen_width - width);
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			/* Swap front and back buffers */
			GLCall(glfwSwapBuffers(window));
		}

	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
