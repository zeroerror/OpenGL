#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_glfw.h>

#include "MVPTest.h"
#include "GLDebug.h"

namespace test {

	MVPTest::MVPTest() {}

	MVPTest::~MVPTest() {}

	void MVPTest::Ctor(const int& screen_width, const int& screen_height) {
		m_screen_width = screen_width;
		m_screen_height = screen_height;
		{
			// Vertext Positions
			int anchorX = screen_width / 2.0f;
			int anchorY = screen_height / 2.0f;
			float positions[16] = {
			   -anchorX,-anchorY,0,0,
			   screen_width - anchorX,-anchorY,1,0,
			   screen_width - anchorX,screen_height - anchorY ,1,1,
			   -anchorX,screen_height - anchorY,0,1,
			};
			std::copy(positions, positions + 16, m_Positions);

			// Vertext Indices
			unsigned int indices[6] = {
			   0, 1, 2,
			   2, 3, 0 };
			std::copy(indices, indices + 6, m_Indices);
		}

		// Vertex Array
		m_va = VertexArray();
		m_va.Ctor();
		m_vb = VertexBuffer();
		m_vb.Ctor(m_Positions, 4 * 4 * sizeof(float));
		m_vb_layout = VertexBufferLayout();
		m_vb_layout.Push<float>(2);
		m_vb_layout.Push<float>(2);
		m_va.AddBuffer(m_vb, m_vb_layout);

		// Index Buffer
		m_ib = IndexBuffer();
		m_ib.Ctor(m_Indices, 6);

		// Shader
		m_Shader = Shader();
		m_Shader.Ctor("res/shader/Basic.shader");

		// Texture 
		m_Texture = Texture();
		m_Texture.Ctor("res/textures/jerry.png");
		m_Texture.Bind();
	}

	void MVPTest::OnRender() {
		GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		Renderer renderer;
		renderer.Clear();

		m_Shader.Bind();
		m_Shader.SetUniform1i("u_Texture", 0);
		m_Shader.SetUniformMat4f("u_MVP", GetMVP(m_TranslationA));
		m_Shader.SetUniform4f("u_BlendColor", 0.0f, 0.0f, 0.0f, 0.8f);
		renderer.Draw(&m_va, &m_ib, &m_Shader);

		m_Shader.Bind();
		m_Shader.SetUniform1i("u_Texture", 0);
		m_Shader.SetUniformMat4f("u_MVP", GetMVP(m_TranslationB));
		m_Shader.SetUniform4f("u_BlendColor", 0.0f, 0.0f, 0.0f, 0.8f);
		renderer.Draw(&m_va, &m_ib, &m_Shader);

	}

	void MVPTest::OnUpdate(const float& deltaTime) {

	}


	void MVPTest::BindRender(VertexArray va, IndexBuffer ib, Shader shader) {
		m_va = va;
		m_ib = ib;
		m_Shader = shader;
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
		glm::mat4 proj = glm::ortho(0.0f, m_screen_width * 2.0f, 0.0f, m_screen_height * 2.0f);
		glm::mat4 mvp = proj * view * model;
		return mvp;
	}

}