#pragma once 

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Test.h"
#include "Camera2D.h"

namespace test {

	class Camera2DTest:public Test {
	public:
		Camera2DTest();
		~Camera2DTest();

		void OnRender() override;
		void OnUpdate(const float& deltaTime) override;

		void Ctor(GLFWwindow* window, const int& screen_width, const int& screen_height);
		//void KeyPressCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	public:
		Camera2D camera;
		GLFWwindow* window;
		const float moveSpeed = 10;

	private:
		glm::vec3 m_TranslationA;
		glm::vec3 m_TranslationB;
		int m_screen_width;
		int m_screen_height;
		TemplateModel m_templateModel;
	};

}