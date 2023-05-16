#pragma once 

#include "Test.h"

namespace test {

	class TestClearColor:public Test {
	public:
		TestClearColor();
		~TestClearColor();

		void OnUpdate(float deltaTime) override;
		void OnRenderer() override;
		void OnImGuiRender() override;
	private:
		float m_ClearColor[4];
		glm::vec3 m_translationA;
		glm::vec3 m_translationB;

	};

}