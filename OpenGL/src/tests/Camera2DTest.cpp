#include "Camera2DTest.h"
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_glfw.h>
#include <GLFW/glfw3.h>

namespace test {

	Camera2DTest::Camera2DTest() {}
	Camera2DTest::~Camera2DTest() {}

	void Camera2DTest::Ctor(GLFWwindow* window, const int& screen_width, const int& screen_height) {

		// ====== Camera
		camera = Camera2D();
		camera.width = screen_width;
		camera.height = screen_height;
		this->window = window;

		// 硬件输入事件注册: 设置窗口的用户指针
		glfwSetWindowUserPointer(window, this);
		glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset) {
			Camera2DTest* camera2DTest = static_cast<Camera2DTest*>(glfwGetWindowUserPointer(window));

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
			m_templateModel.vertexArrayTemp = new float[16];
			std::copy(positions, positions + 16, m_templateModel.vertexArray);
			std::copy(positions, positions + 16, m_templateModel.vertexArrayTemp);
			m_templateModel.vertexCount = 16;

			// Vertext Indices
			unsigned int indices[6] = {
			   0, 1, 2,
			   2, 3, 0 };
			m_templateModel.indiceArray = new unsigned int[6];
			std::copy(indices, indices + 6, m_templateModel.indiceArray);
			m_templateModel.indiceCount = 6;
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
			glm::quat rot = glm::angleAxis(glm::radians(-1.0f), glm::vec3(0, 1, 0));
			glm::quat newRot = rot * m_templateModel.transform.rotation;
			m_templateModel.transform.rotation = newRot;
		}
		if (glfwGetKey(window, GLFW_KEY_RIGHT)) {
			glm::quat rot = glm::angleAxis(glm::radians(1.0f), glm::vec3(0, 1, 0));
			glm::quat newRot = rot * m_templateModel.transform.rotation;
			m_templateModel.transform.rotation = newRot;
		}

		m_templateModel.Update(deltaTime);
		camera.Update(deltaTime);
	}

	void Camera2DTest::OnRender() {
		camera.Render(m_templateModel);
	}

}