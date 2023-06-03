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

		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);
		m_cursorPosX = xPos;
		m_cursorPosY = yPos;

		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		// 硬件输入事件注册: 设置窗口的用户指针
		glfwSetWindowUserPointer(window, this);
		glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset) {
			Camera3DCubeTest* camera3DCubeTest = static_cast<Camera3DCubeTest*>(glfwGetWindowUserPointer(window));
			Transform& camTrans = camera3DCubeTest->camera.transform;
			glm::vec3 pos = camTrans.GetPosition();
			glm::vec3 forward = camTrans.GetForward();
			pos += forward * static_cast<float>(yoffset * camera3DCubeTest->moveSpeed);
			camTrans.SetPosition(pos);
			});

		m_screen_width = screen_width;
		m_screen_height = screen_height;

		// ====== Cube
		m_cube1 = CreateCube(2.0f, 2.0f, 2.0f);
		m_cube1->transform.SetPosition(glm::vec3(0.0f, 0.0f, 5.0f));
		m_cube2 = CreateCube(1.0f, 1.0f, 1.0f);
		m_cube2->transform.SetPosition(glm::vec3(-2.0f, 0.0f, 3.0f));

	}

	Cube* Camera3DCubeTest::CreateCube(const float& width, const float& height, const float& depth) {
		Cube* cube = new Cube();
		cube->Ctor(width, height, depth);
		// - Shader
		cube->shader = new Shader();
		cube->shader->Ctor("res/shader/Cube.shader");
		cube->shader->Bind();
		// - Texture 
		cube->texture = new Texture();
		cube->texture->Ctor("res/textures/jerry.png");
		cube->texture->Bind();
		return cube;
	}

	void Camera3DCubeTest::OnUpdate(const float& deltaTime) {
		//- 相机移动
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
			glm::vec3	forward = camTrans.GetForward();
			camTrans.SetPosition(camTrans.GetPosition() + forward * moveSpeed);
		}
		if (glfwGetKey(window, GLFW_KEY_S)) {
			glm::vec3 forward = camTrans.GetForward();
			camTrans.SetPosition(camTrans.GetPosition() + -forward * moveSpeed);
		}
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);
		double cursorOffsetX = m_cursorPosX - xPos;
		double cursorOffsetY = m_cursorPosY - yPos;
		float xRadius = -glm::radians(cursorOffsetY * rotateSpeed);
		float yRadius = glm::radians(cursorOffsetX * rotateSpeed);
		glm::quat rot = glm::vec3(xRadius, yRadius, 0.0f) * camTrans.GetRotation();
		camTrans.SetRotation(rot);

		camera.Update(deltaTime);
	}

	void Camera3DCubeTest::OnRender() {
		GLCall(glClearColor(0.8f, 0.8f, 0.8f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		GLCall(glEnable(GL_DEPTH_TEST));
		GLCall(glDepthFunc(GL_LESS));
		GLCall(glDepthMask(GL_TRUE));

		camera.Render(m_cube1->transform.GetPosition(), m_cube1->transform.GetRotation(), m_cube1->shader, &m_cube1->va, m_cube1->GetIndexBuffer());
		camera.Render(m_cube2->transform.GetPosition(), m_cube2->transform.GetRotation(), m_cube2->shader, &m_cube2->va, m_cube2->GetIndexBuffer());
	}

}