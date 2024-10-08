#pragma once

#include "VertexArray.h";
#include "IndexBuffer.h"
#include "Shader.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void Clear();
	void SetDrawColor(Shader& shader, const char* uniform, float r, float g, float b, float a);
	void Draw(const VertexArray& vao, const IndexBuffer& ibo, const Shader& shader) const;
private:
	
};

