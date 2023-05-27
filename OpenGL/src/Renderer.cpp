#include "Renderer.h"
#include "GLDebug.h"
#include <GL/glew.h>
#include <string>

#include <iostream>

void Renderer::Clear() const {
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray* va, const IndexBuffer* ib, const Shader* shader) const {

	// Dont Know Why This Works!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	VertexArray vao = VertexArray();
	vao.Ctor();
	VertexBuffer m_vb = VertexBuffer();
	float halfWidth = 1;
	float halfHeight = 1;
	float halfDepth = 1;
	m_vb.Ctor(new float[40]{
		// �������� + ��������
		-halfWidth, -halfHeight, -halfDepth, 0.0f, 0.0f,     // ����0
		halfWidth, -halfHeight, -halfDepth, 1.0f, 0.0f,      // ����1
		halfWidth, halfHeight, -halfDepth, 1.0f, 1.0f,       // ����2
		-halfWidth, halfHeight, -halfDepth, 0.0f, 1.0f,      // ����3
		-halfWidth, -halfHeight, halfDepth, 0.0f, 0.0f,      // ����4
		halfWidth, -halfHeight, halfDepth, 1.0f, 0.0f,       // ����5
		halfWidth, halfHeight, halfDepth, 1.0f, 1.0f,        // ����6
		-halfWidth, halfHeight, halfDepth, 0.0f, 1.0f        // ����7
		}, 40 * sizeof(float));

	VertexBufferLayout m_vbLayout = VertexBufferLayout();
	m_vbLayout.Push<float>(3);
	m_vbLayout.Push<float>(2);

	vao.AddBuffer(m_vb, m_vbLayout);

	// And This Dont Fucking Work!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//va->Bind();

	ib->Bind();
	shader->Bind();
	GLCall(glDrawElements(GL_TRIANGLES, ib->GetCount(), GL_UNSIGNED_INT, nullptr));
}
