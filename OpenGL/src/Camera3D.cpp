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

void Camera3D::Render(glm::vec3 modPosition, glm::quat modRotation,
						Shader* shader, VertexArray* va, IndexBuffer* ib) {
	// - Material
	shader->SetUniform1i("u_Texture", 0);
	//shader->SetUniformMat4f("u_MVP", GetMVPMatrix_Ortho(modTrans));
	shader->SetUniformMat4f("u_MVP", GetMVPMatrix_Perspective(modPosition, modRotation));
	shader->SetUniformMat4f("u_ModRotationMatrix", glm::toMat4(modRotation));
	shader->SetUniform4f("u_BlendColor", 0.0f, 0.0f, 0.0f, 1.0f);

	Renderer renderer;
	renderer.Draw(va, ib, shader);
}

glm::mat4 Camera3D::GetMVPMatrix_Ortho(const glm::vec3& pos, const glm::quat& rot) {
	glm::mat4 model = glm::translate(glm::mat4(1), pos);

	glm::vec3 cameraPos = transform.GetPosition();
	glm::vec3 cameraForward = transform.GetForward();
	glm::vec3 cameraUp = transform.GetUp();
	glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraForward, cameraUp);

	float halfWidth = 10;
	float halfHeight = 10;
	float nearPlane = 0.1f;
	float farPlane = 10.0f;
	glm::mat4 proj = glm::orthoRH(-halfWidth, halfWidth, -halfHeight, halfHeight, nearPlane, farPlane);

	glm::mat4 mvp = proj * view * model;

	return mvp;
}

glm::mat4 Camera3D::GetMVPMatrix_Perspective(const glm::vec3& pos, const glm::quat& rot) {
	glm::mat4 model = glm::translate(glm::mat4(1), pos);

	glm::vec3 cameraPos = transform.GetPosition();
	glm::vec3 cameraForward = transform.GetForward();
	glm::vec3 cameraUp = transform.GetUp();
	glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraForward, cameraUp);

	float constexpr fov = glm::radians(45.0f); // 垂直视场角
	float aspectRatio = width / height; // 宽高比
	float nearPlane = 0.1f;
	float farPlane = 1000.0f;
	glm::mat4 proj = glm::perspectiveRH(fov, aspectRatio, nearPlane, farPlane);

	glm::mat4 mvp = proj * view * model;

	return mvp;
}


