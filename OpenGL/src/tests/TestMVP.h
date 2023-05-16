#pragma once 

#include <glm/gtc/matrix_transform.hpp>

#include "Test.h"

namespace test {

	class TestMVP:public Test {
	public:
		TestMVP();
		~TestMVP();

		void OnUpdate(float deltaTime) override;
		void OnRenderer(const VertexArray& va, const IndexBuffer& ib, Shader& shader) override;
		void OnImGuiRender() override;

		void InjectShader(const Shader shader);
		void SetScreen(const int& screen_width, const int& screen_height);
		glm::mat4 GetMVP(const glm::vec3& translation);
	private:
		float m_ClearColor[4];
		glm::vec3 m_TranslationA;
		glm::vec3 m_TranslationB;
		int m_screen_width;
		int m_screen_height;
		Renderer m_renderer;

	};

}