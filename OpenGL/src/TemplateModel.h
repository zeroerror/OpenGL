#pragma once
#include "Transform.h"
#include "Texture.h"
#include "Shader.h"

class TemplateModel {
public:
	TemplateModel();
	~TemplateModel();

public:
	Transform tranform;
	Texture* texture;
	float* vertexArray;
	unsigned int* indiceArray;
	Shader* shader;

};