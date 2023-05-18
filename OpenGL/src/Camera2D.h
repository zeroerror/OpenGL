#pragma once

#include "TemplateModel.h"
#include "Transform.h"

class Camera2D {
public:
	Camera2D();
	~Camera2D();

	void Update(const float& dt);

	void Render(TemplateModel& model);

	glm::mat4 GetMVPMatrix(const Transform& transform);


public:
	Transform transform;
	unsigned int width;
	unsigned int height;
};
