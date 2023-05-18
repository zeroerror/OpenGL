#include "Camera2D.h"
#include "Renderer.h"
#include "GLDebug.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <GLFW/glfw3.h>

Camera2D::Camera2D() {
}
Camera2D::~Camera2D() {}

void Camera2D::Update(const float& dt) {
	
}

void Camera2D::Render(TemplateModel& model) {
	GLCall(glClear(GL_COLOR_BUFFER_BIT));

	Renderer renderer;
	renderer.Clear();

	Shader* shader = model.shader;
	float* vertexArray = model.vertexArray;
	unsigned int* indiceArray = model.indiceArray;

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

	shader->Bind();
	shader->SetUniform1i("u_Texture", 0);
	shader->SetUniformMat4f("u_MVP", GetMVPMatrix(transform));
	shader->SetUniform4f("u_BlendColor", 0.0f, 0.0f, 0.0f, 0.8f);
	renderer.Draw(&vao, &ibo, shader);
}

glm::mat4 Camera2D::GetMVPMatrix(const Transform& transform) {
	glm::vec3 pos = transform.position;
	glm::quat rot = transform.rotation;
	glm::mat4 model = glm::translate(glm::mat4(1), pos);
	glm::mat4 view = glm::translate(
		glm::mat4(1),
		transform.position
	);
	glm::mat4 proj = glm::ortho(0.0f, width * 2.0f, 0.0f, height * 2.0f);
	glm::mat4 mvp = proj * view * model;
	return mvp;
}

