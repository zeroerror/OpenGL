#include "TestClearColor.h"
#include <imgui/imgui_impl_opengl3.h>

namespace test {

	TestClearColor::TestClearColor()
		:m_ClearColor{ 0.2f,0.3f,0.8f,1.0f }, m_translationA{ 0,0,0 }, m_translationB{ 0,0,0 } {
	
	}

	TestClearColor::~TestClearColor() {

	}

	void TestClearColor::OnUpdate(float deltaTime) {}

	void TestClearColor::OnRenderer() {
		GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}

	void TestClearColor::OnImGuiRender() {
		ImGui::ColorEdit4("Clear Color", m_ClearColor);
		ImGui::SliderFloat2("TranslationA", &m_translationA.x,0,200);
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

}