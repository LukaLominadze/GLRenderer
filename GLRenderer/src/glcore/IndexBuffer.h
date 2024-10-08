#pragma once
class IndexBuffer
{
public:
	IndexBuffer() = default;
	IndexBuffer(const void* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetCount() const { return m_count; }

	void Delete();
private:
	unsigned int m_rendererID;
	unsigned int m_count;
};

