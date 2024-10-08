#include "Input.h"

Input* Input::s_instance = nullptr;

Input::Input(GLFWwindow* p_window)
    :m_mouseStartPos(std::pair<float, float>()), m_mouseEndPos(std::pair<float, float>())
{
    p_nativeWindow = p_window;
    if (!s_instance) {
        s_instance = this;
    }
}

Input::~Input()
{
    s_instance = nullptr;
}

bool Input::IsKeyPressed(int keycode)
{
    int state = glfwGetKey(s_instance->GetNativeWindow(), keycode);
    return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool Input::IsMouseButtonPressed(int button)
{
    int state = glfwGetMouseButton(s_instance->GetNativeWindow(), button);
    return state == GLFW_PRESS;
}

std::pair<float, float> Input::GetMousePosition()
{
    double xpos, ypos;
    glfwGetCursorPos(s_instance->GetNativeWindow(), &xpos, &ypos);
    return std::pair<float, float>((float)xpos, (float)ypos);
}

float Input::GetMouseX()
{
    std::pair<float, float> position = GetMousePosition();
    return position.first;
}

float Input::GetMouseY()
{
    std::pair<float, float> position = GetMousePosition();
    return position.second;
}

void Input::OnUpdate()
{
    m_mouseEndPos = GetMousePosition();
    m_mouseDeltaPos = std::pair<float, float>(m_mouseEndPos.first - m_mouseStartPos.first,
                                              m_mouseEndPos.second - m_mouseStartPos.second);
    m_mouseStartPos = m_mouseEndPos;
}
