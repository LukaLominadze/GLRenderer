#include "glpch.h"

#include "Window.h"

#include "events/ApplicationEvent.h"
#include "events/KeyEvent.h"
#include "events/MouseEvent.h"
#include "DebugNMacros.h"

GLFWwindow* Window::s_nativeWindow = nullptr;

Window::Window(const char* title, uint32_t width, uint32_t height, bool fullscreen = false)
{
    int initialization = glfwInit();
    ASSERT(initialization, "Initializing GLFW...");

    p_monitor = glfwGetPrimaryMonitor();
    p_window = glfwCreateWindow(width, height, title, p_monitor, NULL);
    if (!p_window)
    {
        ERROR_LOG("Failed to create Window! Terminating program...");
        glfwTerminate();
    }


    m_data.Fullscreen = fullscreen;
    if (m_data.Fullscreen) {
        const GLFWvidmode* mode = glfwGetVideoMode(p_monitor);
        m_data.Width = mode->width;
        m_data.Height = mode->height;
        glfwSetWindowMonitor(p_window, p_monitor, 0, 0, m_data.Width, m_data.Height, mode->refreshRate);
        glViewport(0, 0, m_data.Width, m_data.Height);
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

    glfwSetWindowSizeCallback(p_window, [](GLFWwindow* window, int width, int height)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            data.Width = width;
            data.Height = height;
            glViewport(0, 0, data.Width, data.Height);
            WindowResizedEvent event(width, height);
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

void Window::OnEvent(Event& e)
{
    EventDispatcher dispatcher = EventDispatcher(e);
    dispatcher.Dispatch<KeyPressedEvent>(std::bind(&Window::OnFullscreenToggle, this, std::placeholders::_1));
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

bool Window::OnFullscreenToggle(KeyPressedEvent& e)
{
    if (e.GetKeyCode() != GLFW_KEY_F11)
        return false;
    m_data.Fullscreen = !m_data.Fullscreen;
    const GLFWvidmode* mode = glfwGetVideoMode(p_monitor);
    if (m_data.Fullscreen) {
        glfwSetWindowMonitor(p_window, p_monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
        glViewport(0, 0, mode->width, mode->height);
    }
    else {
        int xpos = (mode->width / m_data.Width) / 2;
        int ypos = (mode->height / m_data.Height) / 2 + 40;
        glfwSetWindowMonitor(p_window, NULL, xpos, ypos, m_data.Width, m_data.Height, 0);
    }
    return true;
}
