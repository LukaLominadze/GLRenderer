#include "glpch.h"

#include "Window.h"

#include "events/ApplicationEvent.h"
#include "events/KeyEvent.h"
#include "events/MouseEvent.h"
#include "DebugNMacros.h"

GLFWwindow* Window::s_nativeWindow = nullptr;

Window::Window(const char* title, uint32_t width, uint32_t height)
{
    int initialization = glfwInit();
    ASSERT(initialization, "Initializing GLFW...");

    p_window = glfwCreateWindow(960, 540, title, NULL, NULL);
    if (!p_window)
    {
        ERROR_LOG("Failed to create Window! Terminating program...");
        glfwTerminate();
    }

    glfwMakeContextCurrent(p_window);

    if (!s_nativeWindow) {
        s_nativeWindow = p_window;
    }

    if (glewInit() != GLEW_OK) {
        ERROR_LOG("Couldn't initialize GLEW");
    }

    LOG("OpenGL Info: ")
    LOG("  Vendor: {0} " << glGetString(GL_VENDOR))
    LOG("  Renderer: {0} " << glGetString(GL_RENDERER))
    LOG("  Version: {0} " << glGetString(GL_VERSION))

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    glfwSetWindowUserPointer(p_window, &m_data);

    glfwSetWindowCloseCallback(p_window, [](GLFWwindow* window)
    {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        WindowClosedEvent event;
        data.EventCallback(event);
    });

    glfwSetKeyCallback(p_window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
                case GLFW_PRESS:
                {
                    KeyPressedEvent event(key);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent event(key);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent event(key);
                    data.EventCallback(event);
                    break;
            }
            }
        });

    glfwSetMouseButtonCallback(p_window, [](GLFWwindow* window, int button, int action, int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
                case GLFW_PRESS:
                {
                    MouseButtonPressedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
            }
        });

    glfwSetScrollCallback(p_window, [](GLFWwindow* window, double xOffset, double yOffset)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseScrolledEvent event((float)xOffset, (float)yOffset);
            data.EventCallback(event);
        });
}

Window::~Window()
{
    if (p_window) {
        Delete();
    }
}

void Window::SetVSync(bool value)
{
    if (value)
        glfwSwapInterval(1);
    else
        glfwSwapInterval(0);
}

void Window::OnUpdate()
{
    glfwPollEvents();
    glfwSwapBuffers(p_window);
}

void Window::Delete()
{
    glfwDestroyWindow(p_window);
}
