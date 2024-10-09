#pragma once

#include "Application.h"

extern Application* CreateApplication();

#if GL_PLATFORM_WINDOWS
	#ifdef DISTRIBUTION
	#include <windows.h>
	int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
		Application* app = CreateApplication();
		app->Run();
		delete app;
		return 0;
	}
	#else
	int main() {
		Application* app = CreateApplication();
		app->Run();
		delete app;
	}
	#endif
#endif