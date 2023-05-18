#pragma once 

#include "Test.h"
#include "Texture.h"

#include <glm/gtc/matrix_transform.hpp>

namespace test {

	class MVPTest:public Test {
	public:
		MVPTest();
		~MVPTest();
		void Ctor(const int& screen_width, const int& screen_height);

		void OnUpdate(const float& deltaTime) override;
		void OnRender()override;
		void OnImGuiRender() override;

		void BindRender(VertexArray va, IndexBuffer ib, Shader shader);
		void SetScreen(const int& screen_width, const int& screen_height);
		glm::mat4 GetMVP(const glm::vec3& translation);
	private:
		float m_ClearColor[4];
		float m_Positions[16];
		unsigned int m_Indices[6];
		glm::vec3 m_TranslationA;
		glm::vec3 m_TranslationB;
		int m_screen_width;
		int m_screen_height;
		VertexArray m_va;
		VertexBuffer m_vb;
		VertexBufferLayout m_vb_layout;
		IndexBuffer m_ib;
		Shader m_Shader;
		Texture m_Texture;

	};

}