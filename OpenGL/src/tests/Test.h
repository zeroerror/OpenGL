#pragma once 

#include <GL/glew.h>
#include <ImGui/imgui.h>
#include <functional>
#include <vector>

#include "Renderer.h"

namespace test {

	class Test {

	public:
		Test() {}
		virtual	~Test() {}

		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}

	};

	class TestMenu:public Test {
	public:
		TestMenu(Test*& currentTestPointer);
		~TestMenu();

		void OnImGuiRender() override;

		template<typename T>
		void RegisterTest(const std::string& name) {
			m_Tests.push_back(std::make_pair(name, []() {return new T(); }));
		}

		//template<>
		//void RegisterTest<MVPTest>(const std::string& name)
		//{
		//	std::cout << "Registering test " << name << std::endl;
		//	VertexArray* va = nullptr;
		//	IndexBuffer* ib = nullptr;
		//	Shader* shader = nullptr;
		//	m_Tests.push_back(std::make_pair(name, [va,ib,shader]() {return new MVPTest(va, ib, shader,600,300); }));
		//}

	private:
		Test*& m_CurrentTest;
		std::vector <std::pair<std::string, std::function<Test* ()>>> m_Tests;
	};

}