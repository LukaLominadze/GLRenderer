#pragma once

#include "Test.h"

#include "imgui/imgui.h"

namespace Test
{
	class TestClearColor : public Test
	{
	public:
		TestClearColor();
		~TestClearColor() override;

		void OnRender(Renderer& renderer) override;
		void OnImGuiRender() override;
	private:
		ImVec4 m_clearColor;
	};
}

