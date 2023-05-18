#include "Camera2DTest.h"
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_glfw.h>
#include <GLFW/glfw3.h>

namespace test {

	Camera2DTest::Camera2DTest() {}
	Camera2DTest::~Camera2DTest() {}

	void KeyPressCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		Camera2DTest* camera2DTest = static_cast<Camera2DTest*>(glfwGetWindowUserPointer(window));
		if (camera2DTest && key == GLFW_KEY_A && action == GLFW_PRESS) {
			// 左键
			camera2DTest->m_camera.transform.position += glm::vec3(1, 0, 0);
			glm::vec3 pos = camera2DTest->m_camera.transform.position;
			std::cout << "m_camera.transform.position " << pos.x << "," << pos.y << "," << pos.z << std::endl;
		}
	}

	void Camera2DTest::Ctor(GLFWwindow* window, const int& screen_width, const int& screen_height) {

		// ====== Camera
		m_camera = Camera2D();
		m_camera.width = screen_width;
		m_camera.height = screen_height;

		static glm::vec3 pos;

		// 注册硬件输入事件
		glfwSetWindowUserPointer(window, this); // 设置窗口的用户指针
		glfwSetKeyCallback(window, KeyPressCallback);
		glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset) {
		});

		m_screen_width = screen_width;
		m_screen_height = screen_height;

		// ====== Model
		m_templateModel = TemplateModel();
		{
			// Vertext Positions
			int anchorX = screen_width / 2.0f;
			int anchorY = screen_height / 2.0f;
			float positions[16] = {
			   -anchorX,-anchorY,0,0,
			   screen_width - anchorX,-anchorY,1,0,
			   screen_width - anchorX,screen_height - anchorY ,1,1,
			   -anchorX,screen_height - anchorY,0,1,
			};
			m_templateModel.vertexArray = new float[16];
			std::copy(positions, positions + 16, m_templateModel.vertexArray);

			// Vertext Indices
			unsigned int indices[6] = {
			   0, 1, 2,
			   2, 3, 0 };
			m_templateModel.indiceArray = new unsigned int[6];
			std::copy(indices, indices + 6, m_templateModel.indiceArray);
		}
		// - Shader
		m_templateModel.shader = new Shader();
		m_templateModel.shader->Ctor("res/shader/Basic.shader");
		// - Texture 
		m_templateModel.texture = new Texture();
		m_templateModel.texture->Ctor("res/textures/jerry.png");
		m_templateModel.texture->Bind();

	}

	void Camera2DTest::OnUpdate(const float& deltaTime) {
		m_camera.Update(deltaTime);
	}

	void Camera2DTest::OnRender() {
		m_camera.Render(m_templateModel);
	}

}