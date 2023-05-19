#pragma once
#include "Transform.h"
#include "Texture.h"
#include "Shader.h"

class TemplateModel {
public:
	TemplateModel();
	~TemplateModel();

	void Update(const float& dt);

public:
	Transform transform;
	Texture* texture;
	float* vertexArray;
	unsigned int vertexCount;
	unsigned int* indiceArray;
	unsigned int indiceCount;
	Shader* shader;

};