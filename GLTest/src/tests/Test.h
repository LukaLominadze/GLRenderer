#pragma once

#include <GLRenderer.h>

namespace Test 
{
	class Test {
	public:
		Test() {}
		virtual ~Test() {}

		virtual void OnEvent(Event& event) {}
		virtual void OnUpdate(float timestep) {}
		virtual void OnRender(Renderer& renderer) {}
		virtual void OnImGuiRender() {}
	};

	class TestMenu : public Test {
	public:
		TestMenu(Test*& currentTestPointer);
		~TestMenu() override = default;

		void OnImGuiRender() override;

		template<typename T>
		void RegisterTest(const std::string& name) {
			LOG("Registering test... " << name)
			m_tests.push_back(std::make_pair(name, []() { return new T(); }));
		}
	private:
		Test*& p_currentTest;
		std::vector<std::pair<std::string, std::function<Test* ()>>> m_tests;
	};

	class TestLayer : public Layer {
	public:
		TestLayer();
		virtual ~TestLayer() override = default;

		void OnEvent(Event& event) override;
		void OnUpdate(float timestep) override;
		void OnRender(Renderer& renderer) override;
		void OnImGuiRender() override;
	private:
		TestMenu* p_testMenu;
		Test* p_currentTest;
	};
}