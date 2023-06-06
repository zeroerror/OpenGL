#include "Camera3DCubeTest.h"
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_glfw.h>
#include <GLFW/glfw3.h>
#include <GLDebug.h>
#include <Camera3DController.h>

namespace test {

	Camera3DCubeTest::Camera3DCubeTest() {}
	Camera3DCubeTest::~Camera3DCubeTest() {}

	void Camera3DCubeTest::Ctor(GLFWwindow* window, const int& screen_width, const int& screen_height) {

		// ====== Camera
		camera = Camera3D();
		camera.width = screen_width;
		camera.height = screen_height;
		camera.depth = 1000;
		camera.transform.SetPosition(glm::vec3(0, 0, 10));
		camera.transform.SetRotation(glm::mat4(1.0f));

		this->window = window;

		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);
		m_cursorPosX = xPos;
		m_cursorPosY = yPos;

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

		// ====== Camera Controller
		m_cameraController = Camera3DController();
		m_cameraController.Inject(&camera, window);

		// ====== Cube
		m_cubes[0] = CreateCube(20.0f, 0.5f, 20.0f);
		m_cubes[0]->transform.SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
		for (int i = 1;i < 10;i++) {
			Cube* cube = CreateCube(1.0f + i, 1.0f, 1.0f + i);
			cube->transform.SetPosition(glm::vec3(i * 1.0f, i * 1.0f, i * 1.0f));
			m_cubes[i] = cube;
		}
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
		m_cameraController.Update(deltaTime);
		camera.Update(deltaTime);
	}

	void Camera3DCubeTest::OnRender() {
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		GLCall(glEnable(GL_DEPTH_TEST));
		GLCall(glDepthFunc(GL_LESS));
		GLCall(glDepthMask(GL_TRUE));

		for (size_t i = 0; i < 10; i++)
		{
			Cube* cube = m_cubes[i];
			camera.Render(cube->transform.GetPosition(), cube->transform.GetRotation(), cube->shader, &cube->va, cube->GetIndexBuffer());
		}
	}

}