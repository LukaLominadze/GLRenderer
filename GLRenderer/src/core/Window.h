#pragma once

#include "events/Event.h"
#include "DebugNMacros.h"

#include <functional>

class Window {
public:
	Window() = default;
	Window(const char* title, uint32_t width, uint32_t height);
	~Window();

	inline void SetEventCallback(const std::function<void(Event&)>& function) {
		m_data.EventCallback = function;
	}

	void SetVSync(bool value);

	void OnUpdate();

	inline GLFWwindow* GetNativeWindow() const { return p_window; }
	inline static GLFWwindow* GetGLFWWindow() { return s_nativeWindow; }

	void Delete();
private:
	GLFWwindow* p_window;
	static GLFWwindow* s_nativeWindow;

	struct WindowData {
		uint32_t Width, Height;

		std::function<void(Event&)> EventCallback;
	};

	WindowData m_data;
};