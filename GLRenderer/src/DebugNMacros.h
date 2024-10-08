#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#define DEBUG_LOG(message) \
	std::cout << message << std::endl
#define ERROR_LOG(message) \
	std::cout << message << std::endl; \
	__debugbreak()
#define LOG(message) std::cout << message << std::endl
#define ASSERT(x, message) \
			std::cerr << message; \
			if ((x)){ \
				std::cerr << " -> Success!" << std::endl; \
			} \
			else { \
				std::cerr << " -> Failed!" << std::endl; \
				__debugbreak(); \
			}
#define ASSERT_ERROR(x) \
			if (!(x)){ \
				std::cerr << "Failed!" << std::endl; \
				__debugbreak(); \
			}
#define GLCall(x) x; ASSERT_ERROR(GLLogCall(#x, __FILE__, __LINE__))

inline void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}

inline bool GLLogCall(const char* function, const char* file, int line) {
    while (GLenum error = glGetError()) {
        std::cout << "{OpenGL Error} (" << error << "): " << function << " " << file << std::endl;
        return false;
    }
    return true;
}