#pragma once

#include "events/Event.h"
#include "events/KeyEvent.h"
#include "DebugNMacros.h"

#include <functional>

class Window {
public:
	Window() = default;
	Window(const char* title, uint32_t width, uint32_t height, bool fullscreen);
	~Window();

	inline void SetEventCallback(const std::function<void(Event&)>& function) {
		m_data.EventCallback = function;
	}

	void SetVSync(bool value);

	void OnEvent(Event& e);
	void OnUpdate();

	inline GLFWwindow* GetNativeWindow() const { return p_window; }
	inline static GLFWwindow* GetGLFWWindow() { return s_nativeWindow; }

	void Delete();
private:
	bool OnFullscreenToggle(KeyPressedEvent& e);
private:
	GLFWwindow* p_window;
	GLFWmonitor* p_monitor;
	static GLFWwindow* s_nativeWindow;

	struct WindowData {
		uint32_t Width, Height;
		bool Fullscreen = false;

		std::function<void(Event&)> EventCallback;
	};

	WindowData m_data;

	bool m_isFullscreen = false;
};