#include "rrpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace RoseRoot {
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case RoseRoot::ShaderDataType::Float:  return GL_FLOAT;
		case RoseRoot::ShaderDataType::Float2: return GL_FLOAT;
		case RoseRoot::ShaderDataType::Float3: return GL_FLOAT;
		case RoseRoot::ShaderDataType::Float4: return GL_FLOAT;
		case RoseRoot::ShaderDataType::Mat3:	  return GL_FLOAT;
		case RoseRoot::ShaderDataType::Mat4:	  return GL_FLOAT;
		case RoseRoot::ShaderDataType::Int:	  return GL_INT;
		case RoseRoot::ShaderDataType::Int2:	  return GL_INT;
		case RoseRoot::ShaderDataType::Int3:	  return GL_INT;
		case RoseRoot::ShaderDataType::Int4:	  return GL_INT;
		case RoseRoot::ShaderDataType::Bool:	  return GL_BOOL;
		}

		RR_CORE_ASSERT(false, "Unkown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		RR_PROFILE_FUNCTION();

		glCreateVertexArrays(1, &m_RendererID);
	}
	OpenGLVertexArray::~OpenGLVertexArray()
	{
		RR_PROFILE_FUNCTION();

		glDeleteVertexArrays(1, &m_RendererID);
	}
	void OpenGLVertexArray::Bind() const
	{
		RR_PROFILE_FUNCTION();

		glBindVertexArray(m_RendererID);
	}
	void OpenGLVertexArray::Unbind() const
	{
		RR_PROFILE_FUNCTION();

		glBindVertexArray(0);
	}
	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		RR_PROFILE_FUNCTION();

		RR_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!")

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.GetComponentCount(), ShaderDataTypeToOpenGLBaseType(element.Type), element.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)element.Offset);
			index++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}
	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		RR_PROFILE_FUNCTION();

		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}
}