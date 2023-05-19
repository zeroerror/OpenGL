#include "Camera2DCubeTest.h"
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_glfw.h>
#include <GLFW/glfw3.h>
#include <GLDebug.h>

namespace test {

	Camera2DCubeTest::Camera2DCubeTest() {}
	Camera2DCubeTest::~Camera2DCubeTest() {}

	void Camera2DCubeTest::Ctor(GLFWwindow* window, const int& screen_width, const int& screen_height) {

		// ====== Camera
		camera = Camera2D();
		camera.width = screen_width;
		camera.height = screen_height;
		this->window = window;

		// 硬件输入事件注册: 设置窗口的用户指针
		glfwSetWindowUserPointer(window, this);
		glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset) {
			Camera2DCubeTest* camera2DCubeTest = static_cast<Camera2DCubeTest*>(glfwGetWindowUserPointer(window));

		});

		m_screen_width = screen_width;
		m_screen_height = screen_height;

		// ====== Model
		m_cube = Cube(800, 300, 300);

		// - Shader
		m_cube.shader = new Shader();
		m_cube.shader->Ctor("res/shader/Cube.shader");
		// - Texture 
		m_cube.texture = new Texture();
		m_cube.texture->Ctor("res/textures/jerry.png");
		m_cube.texture->Bind();

	}

	void Camera2DCubeTest::OnUpdate(const float& deltaTime) {
		if (glfwGetKey(window, GLFW_KEY_A)) {
			camera.transform.position += glm::vec3(-1, 0, 0) * moveSpeed;
		}
		if (glfwGetKey(window, GLFW_KEY_D)) {
			camera.transform.position += glm::vec3(1, 0, 0) * moveSpeed;
		}
		if (glfwGetKey(window, GLFW_KEY_W)) {
			camera.transform.position += glm::vec3(0, 1, 0) * moveSpeed;
		}
		if (glfwGetKey(window, GLFW_KEY_S)) {
			camera.transform.position += glm::vec3(0, -1, 0) * moveSpeed;
		}

		// 模型旋转
		if (glfwGetKey(window, GLFW_KEY_LEFT)) {
			glm::quat rot = glm::angleAxis(glm::radians(1.0f), glm::vec3(0, -1, 0));
			glm::quat newRot = rot * m_cube.transform.rotation;
			m_cube.transform.rotation = newRot;
		}
		if (glfwGetKey(window, GLFW_KEY_RIGHT)) {
			glm::quat rot = glm::angleAxis(glm::radians(1.0f), glm::vec3(0, 1, 0));
			glm::quat newRot = rot * m_cube.transform.rotation;
			m_cube.transform.rotation = newRot;
		}
		if (glfwGetKey(window, GLFW_KEY_UP)) {
			glm::quat rot = glm::angleAxis(glm::radians(1.0f), glm::vec3(1, 0, 0));
			glm::quat newRot = rot * m_cube.transform.rotation;
			m_cube.transform.rotation = newRot;
		}
		if (glfwGetKey(window, GLFW_KEY_DOWN)) {
			glm::quat rot = glm::angleAxis(glm::radians(1.0f), glm::vec3(-1, 0, 0));
			glm::quat newRot = rot * m_cube.transform.rotation;
			m_cube.transform.rotation = newRot;
		}

		camera.Update(deltaTime);
	}

	void Camera2DCubeTest::OnRender() {
		GLCall(glClearColor(0.8f, 0.8f, 0.8f, 1.0f));
		camera.Render(m_cube);
	}

}