#include "tests/MVPTest.h"
#include "tests/Camera3DCubeTest.h"
#include "GLDebug.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

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
	int screen_width = 1280;
	int screen_height = 1080;
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

		testMenu->RegisterTest("MVP Test", [screen_width, screen_height]() {
			test::MVPTest* mvpTest = new test::MVPTest();
			mvpTest->Ctor(screen_width, screen_height);
			return mvpTest;
		}
		);

		testMenu->RegisterTest("Camera3D Cube Test", [window, screen_width, screen_height]() {
			test::Camera3DCubeTest* test = new test::Camera3DCubeTest();
			test->Ctor(window, screen_width, screen_height);
			return test;
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
				curTest->OnUpdate(0.1f);
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

