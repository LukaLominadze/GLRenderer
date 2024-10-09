#pragma once

#include "Test.h"

namespace Test
{
	class TestTexture : public Test
	{
	public:
		TestTexture();
		~TestTexture();

		void OnEvent(Event& event) override;
		void OnUpdate(float timestep) override;
		void OnRender(Renderer& renderer) override;
		void OnImGuiRender() override;
	private:
		VertexArray m_vao;
		VertexBuffer m_vbo;
		IndexBuffer m_ibo;
		Shader* p_shader;
		Texture* p_texture;
		ImVec4 m_clearColor;
		ImVec4 m_imageColor;

		OrthographicCameraController m_cameraController;

		glm::vec3 m_translation;
	};
}

