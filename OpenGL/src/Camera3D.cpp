#include "Camera3D.h"
#include "Renderer.h"
#include "GLDebug.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <GLFW/glfw3.h>

Camera3D::Camera3D() {}
Camera3D::~Camera3D() {}

static float u_Time = 0.0f;
void Camera3D::Update(const float& dt) {
	u_Time += dt;
}

void Camera3D::Render(TemplateModel& mod) {
	GLCall(glClear(GL_COLOR_BUFFER_BIT));

	Renderer renderer;
	renderer.Clear();

	Shader* shader = mod.shader;
	float* vertexArray = mod.vertexArray;
	unsigned int* indiceArray = mod.indiceArray;

	VertexArray vao = VertexArray();
	vao.Ctor();
	VertexBuffer vbo = VertexBuffer();
	vbo.Ctor(vertexArray, 4 * 4 * sizeof(float));
	VertexBufferLayout vb_layout = VertexBufferLayout();
	vb_layout.Push<float>(2);
	vb_layout.Push<float>(2);
	vao.AddBuffer(vbo, vb_layout);

	// Index Buffer
	IndexBuffer	ibo = IndexBuffer();
	ibo.Ctor(indiceArray, 6);

	//  - Shader
	Transform modTrans = mod.transform;
	glm::vec3 modPos = modTrans.GetPosition();
	std::cout << "modPos " << modPos.z << std::endl;
	shader->Bind();
	shader->SetUniform1i("u_Texture", 0);
	shader->SetUniformMat4f("u_MVP", GetMVPMatrix_Ortho(modTrans));
	shader->SetUniform3f("u_ModPosition", modPos.x, modPos.y, modPos.z);
	shader->SetUniformMat4f("u_ModRotationMatrix", glm::toMat4(modTrans.GetRotation()));
	shader->SetUniform4f("u_BlendColor", 0.0f, 0.0f, 0.0f, 1.0f);
	renderer.Draw(&vao, &ibo, shader);
}

void Camera3D::Render(Cube& cube) {
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	GLCall(glEnable(GL_DEPTH_TEST));
	GLCall(glDepthFunc(GL_LESS));
	GLCall(glDepthMask(GL_TRUE));

	Renderer renderer;
	renderer.Clear();

	Shader* shader = cube.shader;
	float* vertexArray = cube.vertexArray;
	unsigned int* indiceArray = cube.indiceArray;

	VertexArray vao = VertexArray();
	vao.Ctor();
	VertexBuffer vbo = VertexBuffer();
	vbo.Ctor(vertexArray, 5 * 8 * sizeof(float));
	VertexBufferLayout vb_layout = VertexBufferLayout();
	vb_layout.Push<float>(3);
	vb_layout.Push<float>(2);
	vao.AddBuffer(vbo, vb_layout);

	// Index Buffer
	IndexBuffer	ibo = IndexBuffer();
	ibo.Ctor(indiceArray, 36);

	//  - Shader
	Transform modTrans = cube.transform;
	glm::vec3 modPos = modTrans.GetPosition();
	shader->Bind();
	shader->SetUniform1i("u_Texture", 0);
	//shader->SetUniformMat4f("u_MVP", GetMVPMatrix_Ortho(modTrans));
	shader->SetUniformMat4f("u_MVP", GetMVPMatrix_Perspective(modTrans));
	shader->SetUniform3f("u_ModPosition", modPos.x, modPos.y, modPos.z);
	shader->SetUniformMat4f("u_ModRotationMatrix", glm::toMat4(modTrans.GetRotation()));
	shader->SetUniform4f("u_BlendColor", 0.0f, 0.0f, 0.0f, 1.0f);
	renderer.Draw(&vao, &ibo, shader);
}

glm::mat4 Camera3D::GetMVPMatrix_Ortho(const Transform& modTrans) {
	glm::vec3 pos = modTrans.GetPosition();
	glm::quat rot = modTrans.GetRotation();
	glm::mat4 model = glm::translate(glm::mat4(1), pos);

	glm::mat4 view = glm::translate(glm::mat4(1), -transform.GetPosition());

	float halfWidth = 10;
	float halfHeight = 10;
	float halfDepth = 10;
	glm::mat4 proj = glm::orthoRH(-halfWidth, halfWidth, -halfHeight, halfHeight, halfDepth, -halfDepth);

	glm::mat4 mvp = proj * view * model;

	return mvp;
}

glm::mat4 Camera3D::GetMVPMatrix_Perspective(const Transform& modTrans) {
	glm::vec3 pos = modTrans.GetPosition();
	glm::quat rot = modTrans.GetRotation();
	glm::vec3 cameraPos = transform.GetPosition();

	glm::mat4 model = glm::translate(glm::mat4(1), pos);

	//glm::vec3 cameraTarget = cameraPos + transform.GetForward();
	//glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	//glm::mat4 view = glm::lookAt(cameraPos, cameraTarget, cameraUp);

	// 这里不知道为什么这样才可以解决相机上下左右移动的反转
	cameraPos.x = -cameraPos.x;
	cameraPos.y = -cameraPos.y;
	glm::mat4 view = glm::translate(glm::mat4(1), cameraPos);

	float fov = glm::radians(45.0f); // 垂直视场角
	float aspectRatio = width / height; // 宽高比
	float nearPlane = 0.1f;
	float farPlane = 1000.0f;
	glm::mat4 proj = glm::perspectiveRH(fov, aspectRatio, nearPlane, farPlane);

	glm::mat4 mvp = proj * view * model;

	return mvp;
}


