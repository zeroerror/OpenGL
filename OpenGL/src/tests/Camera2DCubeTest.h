#pragma once 

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Test.h"
#include "Camera2D.h"
#include <Cube.h>

namespace test {

	class Camera2DCubeTest:public Test {
	public:
		Camera2DCubeTest();
		~Camera2DCubeTest();

		void OnRender() override;
		void OnUpdate(const float& deltaTime) override;

		void Ctor(GLFWwindow* window, const int& screen_width, const int& screen_height);
	public:
		Camera2D camera;
		GLFWwindow* window;
		const float moveSpeed = 10;

	private:
		glm::vec3 m_TranslationA;
		glm::vec3 m_TranslationB;
		int m_screen_width;
		int m_screen_height;
		Cube m_cube;
	};

}