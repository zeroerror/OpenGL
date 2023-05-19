#pragma once
#include "Transform.h"
#include <Texture.h>
#include <Shader.h>

class Cube {

public:
	Cube() {};
	Cube(float width, float height, float depth);
	~Cube();

public:
	Transform transform;
	Texture* texture;
	Shader* shader;
	float width;
	float height;
	float depth;
	float* vertexArray;
    static unsigned int indiceArray[];
};

