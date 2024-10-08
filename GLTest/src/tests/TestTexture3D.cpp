#include "TestTexture3D.h"

namespace Test
{
    TestTexture3D::TestTexture3D()
        :m_cameraController(16.0f / 9.0f, 60.0f)
    {
        float positions[] = {
            -0.3f, -0.3f, 0.0f, 0.0f,
             0.3f, -0.3f, 1.0f, 0.0f,
             0.3f,  0.3f, 1.0f, 1.0f,
            -0.3f,  0.3f, 0.0f, 1.0f
        };

        unsigned int indicies[] = {
            0, 1, 2,
            2, 3, 0
        };

        m_vao = VertexArray();
        m_vbo = VertexBuffer(positions, 4 * 4 * sizeof(float));

        VertexBufferLayout layout = VertexBufferLayout();
        layout.Push<float>(2);
        layout.Push<float>(2);
        m_vao.AddBuffer(m_vbo, layout);

        m_ibo = IndexBuffer(indicies, 6);

        //m_projection = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
        //m_view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));


        p_shader = new Shader("src/res/shaders/myShader.shader");

        p_texture = new Texture("src/res/textures/luigi.png");
        p_texture->Bind(0);
        p_shader->SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
        p_shader->SetUniform1i("u_Texture", 0);

        m_vao.Unbind();
        m_vbo.Unbind();
        m_ibo.Unbind();
        p_shader->Unbind();

        m_clearColor = ImVec4(83.0f / 255.0f, 188.0f / 255.0f, 220.0f / 255.0f, 1.0f);
        m_imageColor = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);

        m_translation = glm::vec3(0, 0, -4);
    }

    TestTexture3D::~TestTexture3D()
    {
        p_shader->Delete();
        p_texture->Delete();

        m_vao.Delete();
        m_vbo.Delete();
        m_ibo.Delete();

        delete p_shader;
        delete p_texture;
    }

    void TestTexture3D::OnEvent(Event& event)
    {
        m_cameraController.OnEvent(event);
    }

    void TestTexture3D::OnUpdate(float timestep)
    {
        m_cameraController.OnUpdate(timestep);
    }

    void TestTexture3D::OnRender(Renderer& renderer)
    {
        glm::mat4 model = glm::translate(glm::mat4(1.0f), m_translation);
        glm::mat4 mvp = m_cameraController.GetCamera().GetViewProjectionMatrix() * model;

        GLCall(glClearColor(m_clearColor.x, m_clearColor.y, m_clearColor.z, m_clearColor.w));
        renderer.Clear();

        p_shader->Bind();
        p_shader->SetUniform4f("u_Color", m_imageColor.x, m_imageColor.y, m_imageColor.z, m_imageColor.w);
        p_shader->SetUniformMat4f("u_MVP", mvp);

        renderer.Draw(m_vao, m_ibo, *p_shader);
    }
    void TestTexture3D::OnImGuiRender()
    {
        ImGui::Begin("Hello, world!");

        ImGui::Text("This is some useful text.");

        ImGui::SliderFloat("TranslationX", &m_translation.x, -3.0f, 3.0f);
        ImGui::SliderFloat("TranslationY", &m_translation.y, -2.0f, 2.0f);
        ImGui::SliderFloat("TranslationZ", &m_translation.z, -2.0f, 2.0f);
        ImGui::ColorEdit3("Clear Color", (float*)&m_clearColor);
        ImGui::ColorEdit3("Image Color", (float*)&m_imageColor);

        ImGui::End();
    }
}
