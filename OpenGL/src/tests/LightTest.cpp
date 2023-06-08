#include "LightTest.h"
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_glfw.h>
#include <GLFW/glfw3.h>
#include <GLDebug.h>
#include <Camera3DController.h>

namespace test {

	LightTest::LightTest() {}
	LightTest::~LightTest() {}

	void LightTest::Ctor(GLFWwindow* window, const int& screen_width, const int& screen_height) {

		// ====== Camera
		camera = Camera3D();
		camera.width = screen_width;
		camera.height = screen_height;
		camera.depth = 1000;
		camera.transform.SetPosition(glm::vec3(0, 0, 20));
		camera.transform.SetRotation(glm::quat(glm::vec3(0, 0, 0)));

		this->window = window;

		// 硬件输入事件注册: 设置窗口的用户指针
		glfwSetWindowUserPointer(window, this);
		glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset) {
			LightTest* camera3DCubeTest = static_cast<LightTest*>(glfwGetWindowUserPointer(window));
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
		m_cubes[0]->transform.SetRotation(glm::quat(glm::vec3(0, 0, 0)));
		for (int i = 1;i < 10;i++) {
			Cube* cube = CreateCube(1.0f + i, 1.0f, 1.0f + i);
			cube->transform.SetPosition(glm::vec3(i * 1.0f, i * 1.0f, i * 1.0f));
			cube->transform.SetRotation(glm::angleAxis(glm::radians(18.0f * i), glm::vec3(0.0f, 1.0f, 0.0f)));
			m_cubes[i] = cube;
		}
	}

	Cube* LightTest::CreateCube(const float& width, const float& height, const float& depth) {
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

	void LightTest::OnUpdate(const float& deltaTime) {
		m_cameraController.Update(deltaTime);
		camera.Update(deltaTime);
	}

	void LightTest::OnRender() {
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		GLCall(glEnable(GL_DEPTH_TEST));
		GLCall(glDepthFunc(GL_LESS));
		GLCall(glDepthMask(GL_TRUE));


		// 设置光源属性
		GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 }; // 光源位置
		GLfloat light_color[] = { 1.0, 1.0, 1.0, 1.0 }; // 光源颜色
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color);

		// 设置材质属性
		GLfloat material_diffuse[] = { 0.8, 0.8, 0.8, 1.0 }; // 漫反射颜色
		GLfloat material_specular[] = { 1.0, 1.0, 1.0, 1.0 }; // 镜面反射颜色
		GLfloat material_shininess[] = { 50.0 }; // 高光指数
		glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);

		// 启用光照
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);

		for (size_t i = 0; i < 10; i++)
		{
			Cube* cube = m_cubes[i];
			camera.Render(cube->transform.GetPosition(), cube->transform.GetRotation(), cube->shader, &cube->va, cube->GetIndexBuffer());
		}
	}

}