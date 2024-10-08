#include "Renderer.h"
#include "DebugNMacros.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::Clear()
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::SetDrawColor(Shader& shader, const char* uniform, float r, float g, float b, float a)
{
	shader.Bind();
	shader.SetUniform4f(uniform, r, g, b, a);
	shader.Unbind();
}

void Renderer::Draw(const VertexArray& vao, const IndexBuffer& ibo, const Shader& shader) const
{
	vao.Bind();
	ibo.Bind();
	shader.Bind();
	GLCall(glDrawElements(GL_TRIANGLES, ibo.GetCount(), GL_UNSIGNED_INT, nullptr));
}
