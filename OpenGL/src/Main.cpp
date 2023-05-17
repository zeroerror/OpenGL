#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"
#include "tests/MVPTest.h"

int main() {
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
		unsigned int width = 800;
		unsigned int height = 600;
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

		// IMGUI Context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init();

		// TEST
		test::Test* curTest = nullptr;
		test::TestMenu* testMenu = new test::TestMenu(curTest);
		curTest = testMenu;

		testMenu->RegisterTest("MVP Test", [&va, &ib, &shader, screen_width, screen_height]() {
			return new test::MVPTest(&va, &ib, &shader, screen_width, screen_height);
			}
		);

		while (!glfwWindowShouldClose(window)) {
			GLCall(glfwPollEvents());
			GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
			GLCall(glClear(GL_COLOR_BUFFER_BIT));

			ImGui_ImplGlfw_NewFrame();
			ImGui_ImplOpenGL3_NewFrame();
			ImGui::NewFrame();

			if (curTest) {
				curTest->OnUpdate(0.0f);
				curTest->OnRender();
				ImGui::Begin("Test");
				if (curTest != testMenu && ImGui::Button("<-")) {
					delete curTest;
					curTest = testMenu;
				}
				curTest->OnImGuiRender();
				ImGui::End();
			}

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			/* Swap front and back buffers */
			GLCall(glfwSwapBuffers(window));
		}

		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

