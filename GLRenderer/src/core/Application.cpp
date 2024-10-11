#include "glpch.h"

#include "Application.h"

Application::Application(const char* title, uint32_t width, uint32_t height, bool vsync, bool fullscreen = false)
    :m_running(false)
{
    p_window = new Window(title, width, height, fullscreen);
    p_window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
    p_window->SetVSync(vsync);

    p_input = new Input(p_window->GetNativeWindow());

    m_renderer = Renderer();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    const char* glsl_version = "#version 130";

    ImGui_ImplGlfw_InitForOpenGL(p_window->GetNativeWindow(), true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    ImGui::StyleColorsDark();
}

Application::~Application()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    delete p_input;
    p_window->Delete();

    glfwTerminate();
}

void Application::Run()
{
    Test::Timer timer = Test::Timer();
    float timestep = 0.0f;

    m_running = true;

    while (m_running)
    {
        timer.StartTimerAndReturnSeconds();

        OnUpdate(timestep);

        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
        m_renderer.Clear();
        
        OnRender();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        OnImGuiRender();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        p_window->OnUpdate();

        timestep = timer.EndTimerAndReturnSeconds();
    }
}

void Application::PushLayer(Layer* layer)
{
    m_layerStack.push_back(layer);
    layer->OnAttach();
}

void Application::OnEvent(Event& event)
{
    if (event.GetEventType() == EventType::WindowClose)
        m_running = false;
    p_window->OnEvent(event);
    for (int i = m_layerStack.size() - 1; i >= 0; i--) {
        m_layerStack[i]->OnEvent(event);
    }
}

void Application::OnUpdate(float timestep)
{
    p_input->OnUpdate();
    for (Layer* layer : m_layerStack) {
        layer->OnUpdate(timestep);
    }
}

void Application::OnRender()
{
    for (Layer* layer : m_layerStack) {
        layer->OnRender(m_renderer);
    }
}

void Application::OnImGuiRender()
{
    for (Layer* layer : m_layerStack) {
        layer->OnImGuiRender();
    }
}
