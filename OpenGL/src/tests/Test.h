#pragma once 

#include <GL/glew.h>
#include <ImGui/imgui.h>

#include "Renderer.h"

namespace test {

	class Test {

	public:
		Test(){}
		virtual	~Test(){}

		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRenderer() {}
		virtual void OnImGuiRender() {}

	};

}