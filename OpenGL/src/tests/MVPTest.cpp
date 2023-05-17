#include "MVPTest.h"
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_glfw.h>

namespace test {

	MVPTest::MVPTest()
		:m_ClearColor{ 0.2f, 0.3f, 0.8f, 1.0f },
		m_TranslationA{ 0, 0, 0 },
		m_TranslationB{ 0, 0, 0 },
		m_renderer(),
		m_va(),
		m_ib(),
		m_shader(),
		m_screen_width(600),
		m_screen_height(300)
	{
	}

	//MVPTest::MVPTest(VertexArray* va, IndexBuffer* ib, Shader* shader, const int& screen_width, const int& screen_height)
	//	:m_ClearColor{ 0.2f, 0.3f, 0.8f, 1.0f },
	//	m_TranslationA{ 0, 0, 0 },
	//	m_TranslationB{ 0, 0, 0 },
	//	m_renderer(),
	//	m_va(va),
	//	m_ib(ib),
	//	m_shader(shader),
	//	m_screen_width(screen_width),
	//	m_screen_height(screen_height)
	//{
	//}

	MVPTest::~MVPTest() {
	
	}

	void MVPTest::OnRender() {
		GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));

		if (m_renderer != nullptr) {
			m_renderer->Clear();

			m_shader->Bind();
			m_shader->SetUniform1i("u_Texture", 0);
			m_shader->SetUniformMat4f("u_MVP", GetMVP(m_TranslationA));
			m_shader->SetUniform4f("u_BlendColor", 0.0f, 0.0f, 0.0f, 0.8f);
			m_renderer->Draw(m_va, m_ib, m_shader);

			m_shader->Bind();
			m_shader->SetUniform1i("u_Texture", 0);
			m_shader->SetUniformMat4f("u_MVP", GetMVP(m_TranslationB));
			m_shader->SetUniform4f("u_BlendColor", 1.0f, 0.0f, 0.0f, 0.8f);
			m_renderer->Draw(m_va, m_ib, m_shader);
		}

		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}

	void MVPTest::OnUpdate(float deltaTime) {

	}


	void MVPTest::BindRender(VertexArray* va, IndexBuffer* ib, Shader* shader) {
		this->m_va = va;
		this->m_ib = ib;
		this->m_shader = shader;
	}

	void MVPTest::OnImGuiRender() {
		ImGui::ColorEdit4("Clear Color", m_ClearColor);
		ImGui::SliderFloat2("TranslationA", &m_TranslationA.x, 0, m_screen_width);
		ImGui::SliderFloat2("TranslationB", &m_TranslationB.x, 0, m_screen_width);
	}

	void MVPTest::SetScreen(const int& screen_width, const int& screen_height) {
		m_screen_width = screen_width;
		m_screen_height = screen_height;
	}

	glm::mat4 MVPTest::GetMVP(const glm::vec3& translation) {
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