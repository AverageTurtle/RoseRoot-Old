#include "vepch.h"
#include "RendererVoxel.h"

#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

namespace VoxelEngine {

	struct RendererVoxelStorage
	{
		Ref<VertexArray> QuadVertexArray;
		Ref<Shader> TextureShader;
		Ref<Texure2D> WhiteTexture;
	};

	static RendererVoxelStorage* s_Data;

	void RendererVoxel::Init()
	{
		s_Data = new RendererVoxelStorage();
		s_Data->QuadVertexArray = VertexArray::Create();

		float quadVertices[4 * 5] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
		};

		Ref<VertexBuffer> quadVertexBuffer;
		quadVertexBuffer.reset(VertexBuffer::Create(quadVertices, sizeof(quadVertices)));
		quadVertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float2, "a_TexCoord" }
		});
		s_Data->QuadVertexArray->AddVertexBuffer(quadVertexBuffer);

		uint32_t quadIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Ref<IndexBuffer> quadIndexBuffer;
		quadIndexBuffer.reset(IndexBuffer::Create(quadIndices, sizeof(quadIndices) / sizeof(uint32_t)));
		s_Data->QuadVertexArray->SetIndexBuffer(quadIndexBuffer);

		s_Data->WhiteTexture = Texure2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_Data->WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		s_Data->TextureShader = Shader::Create("assets/shaders/Block.glsl");
		s_Data->TextureShader->Bind();
		s_Data->TextureShader->SetInt("u_Texture", 0);
	}

	void RendererVoxel::Shutdown()
	{
		delete s_Data;
	}

	void RendererVoxel::BeginScene(const PerspectiveCamera& camera)
	{
		s_Data->TextureShader->Bind();
		s_Data->TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	}

	void RendererVoxel::EndScene()
	{

	}

	void RendererVoxel::DrawQuad(const glm::vec3& position, const glm::vec3& scale, const glm::vec3& rotation, const glm::vec4& color)
	{
		s_Data->TextureShader->SetFloat4("u_Color", color);
		s_Data->WhiteTexture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), scale)
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f)) 
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f)) 
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));

		s_Data->TextureShader->SetMat4("u_Transform", transform);

		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}
	void RendererVoxel::DrawQuad(const glm::vec3& position, const glm::vec3& scale, const glm::vec3& rotation, const glm::vec4& color, const Ref<Texure2D>& texture)
	{
		s_Data->TextureShader->SetFloat4("u_Color", color);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), scale)
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f))
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f))
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));
		s_Data->TextureShader->SetMat4("u_Transform", transform);

		texture->Bind();

		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}
}