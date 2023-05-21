#pragma once

#include "TemplateModel.h"
#include "Transform.h"
#include <Cube.h>

class Camera3D {
public:
	Camera3D();
	~Camera3D();

	void Update(const float& dt);

	void Render(TemplateModel& model);
	void Render(Cube& cube);

	glm::mat4 GetMVPMatrix_Ortho(const Transform& transform);
	glm::mat4 GetMVPMatrix_Perspective(const Transform& transform);


public:
	Transform transform;
	float width;
	float height;
	float depth;

};
