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
			glm::vec3 forward = camTrans.GetForward();
			pos += forward * static_cast<float>(yoffset * camera3DCubeTest->moveSpeed);
			camTrans.SetPosition(pos);
			std::cout << "camTrans pos " << pos.x << ", " << pos.y << ", " << pos.z << std::endl;
			});

		m_screen_width = screen_width;
		m_screen_height = screen_height;

		// ====== Cube
		m_cube1 = CreateCube(1.5f, 2.0f, 1.0f);
		m_cube1.transform.SetPosition(glm::vec3(0, 0, 5));

		//m_cube2 = CreateCube(2.0f, 3.0f, 1.0f);
		//m_cube2.transform.SetPosition(glm::vec3(-5, 5, 3));
	}

	Cube Camera3DCubeTest::CreateCube(const float& width, const float& height, const float& depth) {
		Cube cube = Cube(width, height, depth);

		// - Shader
		cube.shader = new Shader();
		cube.shader->Ctor("res/shader/Cube.shader");
		cube.shader->Bind();
		// - Texture 
		cube.texture = new Texture();
		cube.texture->Ctor("res/textures/jerry.png");
		cube.texture->Bind();
		return cube;
	}

	void Camera3DCubeTest::OnUpdate(const float& deltaTime) {
		// 相机移动
		Transform& camTrans = camera.transform;
		if (glfwGetKey(window, GLFW_KEY_A)) {
			glm::vec3 right = camTrans.GetRight();
			camTrans.SetPosition(camTrans.GetPosition() + -right * moveSpeed);
		}
		if (glfwGetKey(window, GLFW_KEY_D)) {
			glm::vec3 right = camTrans.GetRight();
			camTrans.SetPosition(camTrans.GetPosition() + right * moveSpeed);
		}
		if (glfwGetKey(window, GLFW_KEY_W)) {
			glm::vec3 up = camTrans.GetUp();
			camTrans.SetPosition(camTrans.GetPosition() + up * moveSpeed);
		}
		if (glfwGetKey(window, GLFW_KEY_S)) {
			glm::vec3 up = camTrans.GetUp();
			camTrans.SetPosition(camTrans.GetPosition() + -up * moveSpeed);
		}

		// 模型旋转
		if (glfwGetKey(window, GLFW_KEY_LEFT)) {
			glm::quat rot = glm::angleAxis(glm::radians(1.0f), glm::vec3(0, -1, 0));
			glm::quat newRot = rot * m_cube1.transform.GetRotation();
			m_cube1.transform.SetRotation(newRot);
		}
		if (glfwGetKey(window, GLFW_KEY_RIGHT)) {
			glm::quat rot = glm::angleAxis(glm::radians(1.0f), glm::vec3(0, 1, 0));
			glm::quat newRot = rot * m_cube1.transform.GetRotation();
			m_cube1.transform.SetRotation(newRot);
		}
		if (glfwGetKey(window, GLFW_KEY_UP)) {
			glm::quat rot = glm::angleAxis(glm::radians(1.0f), glm::vec3(1, 0, 0));
			glm::quat newRot = rot * m_cube1.transform.GetRotation();
			m_cube1.transform.SetRotation(newRot);
		}
		if (glfwGetKey(window, GLFW_KEY_DOWN)) {
			glm::quat rot = glm::angleAxis(glm::radians(1.0f), glm::vec3(-1, 0, 0));
			glm::quat newRot = rot * m_cube1.transform.GetRotation();
			m_cube1.transform.SetRotation(newRot);
		}

		camera.Update(deltaTime);
	}

	void Camera3DCubeTest::OnRender() {
		GLCall(glClearColor(0.8f, 0.8f, 0.8f, 1.0f));
		camera.Render(m_cube1);
		//camera.Render(m_cube2);
	}

}