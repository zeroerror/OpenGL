#include "Cube.h"
#include "Transform.h"
#include <Texture.h>
#include <Shader.h>

Cube::Cube(float width, float height, float depth) {
	this->width = width;
	this->height = height;
	this->depth = depth;
	float halfWidth = width / 2.0f;
	float halfHeight = height / 2.0f;
	float halfDepth = depth / 2.0f;

	this->vertexArray = new float[40]{
		// 顶点坐标 + 纹理坐标
		-halfWidth, -halfHeight, -halfDepth, 0.0f, 0.0f,     // 顶点0
		halfWidth, -halfHeight, -halfDepth, 1.0f, 0.0f,      // 顶点1
		halfWidth, halfHeight, -halfDepth, 1.0f, 1.0f,       // 顶点2
		-halfWidth, halfHeight, -halfDepth, 0.0f, 1.0f,      // 顶点3
		-halfWidth, -halfHeight, halfDepth, 0.0f, 0.0f,      // 顶点4
		halfWidth, -halfHeight, halfDepth, 1.0f, 0.0f,       // 顶点5
		halfWidth, halfHeight, halfDepth, 1.0f, 1.0f,        // 顶点6
		-halfWidth, halfHeight, halfDepth, 0.0f, 1.0f        // 顶点7
	};

}

Cube::~Cube() {}


unsigned int Cube::indiceArray[36] = {
	0, 1, 2,  // 面0
	2, 3, 0,
	1, 5, 6,  // 面1
	6, 2, 1,
	5, 4, 7,  // 面2
	7, 6, 5,
	4, 0, 3,  // 面3
	3, 7, 4,
	3, 2, 6,  // 面4
	6, 7, 3,
	4, 5, 1,  // 面5
	1, 0, 4
};