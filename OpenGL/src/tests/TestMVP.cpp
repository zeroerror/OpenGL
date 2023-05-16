#include "TestMVP.h"
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_glfw.h>

namespace test {

	TestMVP::TestMVP()
		:m_ClearColor{ 0.2f, 0.3f, 0.8f, 1.0f },
		m_TranslationA{ 0, 0, 0 },
		m_TranslationB{ 0, 0, 0 },
		m_screen_width(0),
		m_screen_height(0),
		m_renderer()
	{
	}

	TestMVP::~TestMVP() {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void TestMVP::OnUpdate(float deltaTime) {

	}

	void TestMVP::OnRenderer(const VertexArray& va, const IndexBuffer& ib, Shader& shader) {

		GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
		m_renderer.Clear();

		shader.Bind();
		shader.SetUniform1i("u_Texture", 0);
		shader.SetUniformMat4f("u_MVP", GetMVP(m_TranslationA));
		shader.SetUniform4f("u_BlendColor", 0.0f, 0.0f, 0.0f, 0.8f);
		m_renderer.Draw(va, ib, shader);

		shader.Bind();
		shader.SetUniform1i("u_Texture", 0);
		shader.SetUniformMat4f("u_MVP", GetMVP(m_TranslationB));
		shader.SetUniform4f("u_BlendColor", 1.0f, 0.0f, 0.0f, 0.8f);
		m_renderer.Draw(va, ib, shader);
	}

	void TestMVP::OnImGuiRender() {
		ImGui::ColorEdit4("Clear Color", m_ClearColor);
		ImGui::SliderFloat2("TranslationA", &m_TranslationA.x, 0, m_screen_width);
		ImGui::SliderFloat2("TranslationB", &m_TranslationB.x, 0, m_screen_width);
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void TestMVP::InjectShader(const Shader shader) {}

	void TestMVP::SetScreen(const int& screen_width, const int& screen_height) {
		m_screen_width = screen_width;
		m_screen_height = screen_height;
	}

	glm::mat4 TestMVP::GetMVP(const glm::vec3& translation) {
		glm::mat4 model = glm::translate(glm::mat4(1), translation);
		glm::mat4 view = glm::translate(
			glm::mat4(1),
			glm::vec3(0, 0, 0)
		);
		glm::mat4 proj = glm::ortho(0.0f, m_screen_width * 1.0f, 0.0f, m_screen_height * 1.0f);
		glm::mat4 mvp = proj * view * model;
		return mvp;
	}

}