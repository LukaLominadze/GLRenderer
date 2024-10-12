#pragma once

#include "Test.h"

namespace Test
{
	class TestTexture3D : public Test
	{
	public:
		TestTexture3D();
		~TestTexture3D();

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

		PerspectiveCameraController m_cameraController;

		glm::vec3 m_translation;
		glm::vec3 m_scale;
	};
}

