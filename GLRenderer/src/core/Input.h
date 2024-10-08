#pragma once

#include "Window.h"

class Input {
public:
	Input(GLFWwindow* p_window);
	~Input();

	static bool IsKeyPressed(int keycode);
	static bool IsMouseButtonPressed(int button);
	static std::pair<float, float> GetMousePosition();
	inline static std::pair<float, float> GetMousePositionDelta() { return s_instance->GetMousePosDelta(); }
	static float GetMouseX();
	static float GetMouseY();

	void OnUpdate();

	inline const std::pair<float, float>& GetMousePosDelta() { return m_mouseDeltaPos; }
	GLFWwindow* GetNativeWindow() const { return p_nativeWindow; }
private:
	static Input* s_instance;

	GLFWwindow* p_nativeWindow;

	std::pair<float, float> m_mouseStartPos;
	std::pair<float, float> m_mouseEndPos;
	std::pair<float, float> m_mouseDeltaPos;
};