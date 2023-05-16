#pragma once 

#include <glm/gtc/matrix_transform.hpp>

#include "Test.h"

namespace test {

	class TestClearColor:public Test {
	public:
		TestClearColor();
		~TestClearColor();

		void OnUpdate(float deltaTime) override;
		void OnRenderer() override;
		void OnImGuiRender() override;

		void InjectShader(const Shader shader);
		void SetScreen(const int& screen_width, const int& screen_height);
	private:
		float m_ClearColor[4];
		glm::vec3 m_translationA;
		glm::vec3 m_translationB;
		int m_screen_width;
		int m_screen_height;

	};

}