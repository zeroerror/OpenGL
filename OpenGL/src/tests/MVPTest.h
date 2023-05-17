#pragma once 

#include <glm/gtc/matrix_transform.hpp>

#include "Test.h"

namespace test {

	class MVPTest:public Test {
	public:
		MVPTest(VertexArray* va, IndexBuffer* ib, Shader* shader, const int& screen_width, const int& screen_height);
		~MVPTest();

		void OnUpdate(float deltaTime) override;
		void OnRender()override;
		void OnImGuiRender() override;

		void BindRender(VertexArray* va, IndexBuffer* ib, Shader* shader);
		void SetScreen(const int& screen_width, const int& screen_height);
		glm::mat4 GetMVP(const glm::vec3& translation);
	private:
		float m_ClearColor[4];
		glm::vec3 m_TranslationA;
		glm::vec3 m_TranslationB;
		int m_screen_width;
		int m_screen_height;
		VertexArray* m_va;
		IndexBuffer* m_ib;
		Shader* m_shader;

	};

}