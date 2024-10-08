#include "Test.h"
#include "TestClearColor.h"
#include "TestTexture.h"
#include "TestTexture3D.h"

#include "imgui/imgui.h"

namespace Test 
{
	TestMenu::TestMenu(Test*& currentTestPointer)
		:p_currentTest(currentTestPointer)
	{
	}

	void TestMenu::OnImGuiRender()
	{
		for (std::pair<std::string, std::function<Test*()>>& test : m_tests) {
			if (ImGui::Button(test.first.c_str())) {
				p_currentTest = test.second();
			}
		}
	}

	TestLayer::TestLayer()
	{
		p_testMenu = new TestMenu(p_currentTest);
		p_currentTest = p_testMenu;
		p_testMenu->RegisterTest<TestClearColor>("Clear Color");
		p_testMenu->RegisterTest<TestTexture>("Texture");
		p_testMenu->RegisterTest<TestTexture3D>("Texture3D");
	}

	void TestLayer::OnEvent(Event& event)
	{
		p_currentTest->OnEvent(event);
	}

	void TestLayer::OnUpdate(float timestep)
	{
		p_currentTest->OnUpdate(timestep);
	}

	void TestLayer::OnRender(Renderer& renderer)
	{
		p_currentTest->OnRender(renderer);
	}

	void TestLayer::OnImGuiRender()
	{
		ImGui::Begin("Test");
		if (p_currentTest != p_testMenu && ImGui::Button("<-")) {
			delete p_currentTest;
			p_currentTest = p_testMenu;
		}
		p_currentTest->OnImGuiRender();
		ImGui::End();
	}
}