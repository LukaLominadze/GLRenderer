#include "TestClearColor.h"

#include "DebugNMacros.h";

namespace Test
{
	TestClearColor::TestClearColor()
	{
		m_clearColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	}

	TestClearColor::~TestClearColor()
	{
	}

	void TestClearColor::OnRender(Renderer& renderer)
	{
		GLCall(glClearColor(m_clearColor.x, m_clearColor.y, m_clearColor.z, m_clearColor.w));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}

	void TestClearColor::OnImGuiRender()
	{
		ImGui::ColorEdit4("Clear Color", (float*)&m_clearColor);
	}
}
