#include "Camera3DCubeTest.h"
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_glfw.h>
#include <GLFW/glfw3.h>
#include <GLDebug.h>

namespace test {

	Camera3DCubeTest::Camera3DCubeTest() {}
	Camera3DCubeTest::~Camera3DCubeTest() {}

	void Camera3DCubeTest::Ctor(GLFWwindow* window, const int& screen_width, const int& screen_height) {

		// ====== Camera
		camera = Camera3D();
		camera.width = screen_width;
		camera.height = screen_height;
		camera.depth = 1000;
		this->window = window;

		// 硬件输入事件注册: 设置窗口的用户指针
		glfwSetWindowUserPointer(window, this);
		glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset) {
			Camera3DCubeTest* camera3DCubeTest = static_cast<Camera3DCubeTest*>(glfwGetWindowUserPointer(window));
			Transform& camTrans = camera3DCubeTest->camera.transform;
			glm::vec3 pos = camTrans.GetPosition();
			pos.z += yoffset;
			camTrans.SetPosition(pos);
			std::cout << "camTrans pos " << pos.x << ", " << pos.y << ", " << pos.z << std::endl;
			});

		m_screen_width = screen_width;
		m_screen_height = screen_height;

		// ====== Cube
		m_cube = Cube(1.5f, 2.0f, 1.0f);
		m_cube.transform.SetPosition(glm::vec3(2, 0, 0));

		// - Shader
		m_cube.shader = new Shader();
		m_cube.shader->Ctor("res/shader/Cube.shader");
		m_cube.shader->Bind();
		// - Texture 
		m_cube.texture = new Texture();
		m_cube.texture->Ctor("res/textures/jerry.png");
		m_cube.texture->Bind();
	}

	void Camera3DCubeTest::OnUpdate(const float& deltaTime) {
		// 相机移动
		Transform& camTrans = camera.transform;
		if (glfwGetKey(window, GLFW_KEY_A)) {
			camTrans.SetPosition(camTrans.GetPosition() + glm::vec3(-1, 0, 0) * moveSpeed);
		}
		if (glfwGetKey(window, GLFW_KEY_D)) {
			camTrans.SetPosition(camTrans.GetPosition() + glm::vec3(1, 0, 0) * moveSpeed);
		}
		if (glfwGetKey(window, GLFW_KEY_W)) {
			camTrans.SetPosition(camTrans.GetPosition() + glm::vec3(0, 1, 0) * moveSpeed);
		}
		if (glfwGetKey(window, GLFW_KEY_S)) {
			camTrans.SetPosition(camTrans.GetPosition() + glm::vec3(0, -1, 0) * moveSpeed);
		}

		// 模型旋转
		if (glfwGetKey(window, GLFW_KEY_LEFT)) {
			glm::quat rot = glm::angleAxis(glm::radians(1.0f), glm::vec3(0, -1, 0));
			glm::quat newRot = rot * m_cube.transform.GetRotation();
			m_cube.transform.SetRotation(newRot);
		}
		if (glfwGetKey(window, GLFW_KEY_RIGHT)) {
			glm::quat rot = glm::angleAxis(glm::radians(1.0f), glm::vec3(0, 1, 0));
			glm::quat newRot = rot * m_cube.transform.GetRotation();
			m_cube.transform.SetRotation(newRot);
		}
		if (glfwGetKey(window, GLFW_KEY_UP)) {
			glm::quat rot = glm::angleAxis(glm::radians(1.0f), glm::vec3(1, 0, 0));
			glm::quat newRot = rot * m_cube.transform.GetRotation();
			m_cube.transform.SetRotation(newRot);
		}
		if (glfwGetKey(window, GLFW_KEY_DOWN)) {
			glm::quat rot = glm::angleAxis(glm::radians(1.0f), glm::vec3(-1, 0, 0));
			glm::quat newRot = rot * m_cube.transform.GetRotation();
			m_cube.transform.SetRotation(newRot);
		}

		camera.Update(deltaTime);
	}

	void Camera3DCubeTest::OnRender() {
		GLCall(glClearColor(0.8f, 0.8f, 0.8f, 1.0f));
		camera.Render(m_cube);
	}

}