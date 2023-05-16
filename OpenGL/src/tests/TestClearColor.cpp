#include "TestClearColor.h"
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_glfw.h>

namespace test {

	TestClearColor::TestClearColor()
		:m_ClearColor{ 0.2f, 0.3f, 0.8f, 1.0f },
		m_translationA{ 0, 0, 0 },
		m_translationB{ 0, 0, 0 },
		m_screen_width(0),
		m_screen_height(0) {
	}

	TestClearColor::~TestClearColor() {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void TestClearColor::OnUpdate( float deltaTime) {

	}

	void TestClearColor::OnRenderer() {

		GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		//// MVP
		//glm::mat4 model = glm::translate(glm::mat4(1), glm::vec3(1, 1, 1));
		//glm::mat4 view = glm::translate(
		//	glm::mat4(1),
		//	glm::vec3(0, 0, 0)
		//);
		//glm::mat4 proj = glm::ortho(0.0f, m_screen_width * 1.0f, 0.0f, m_screen_height * 1.0f);
		//glm::mat4 mvp = proj * view * model;

		//shader.Bind();
		//shader.SetUniform1i("u_Texture", 0);
		//shader.SetUniformMat4f("u_MVP", mvp);
		//shader.SetUniform4f("u_BlendColor", 0.8f, 0.0f, 0.0f, 0.8f);
	}

	void TestClearColor::OnImGuiRender() {
		ImGui::ColorEdit4("Clear Color", m_ClearColor);
		ImGui::SliderFloat2("TranslationA", &m_translationA.x, 0, 200);
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void TestClearColor::InjectShader(const Shader shader) {}

	void TestClearColor::SetScreen(const int& screen_width, const int& screen_height) {

	}

}