#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

class Transform {
public:
	Transform();
	~Transform();

public:
	glm::vec3 position;
	glm::quat rotation;
};
