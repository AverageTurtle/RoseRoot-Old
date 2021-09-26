#include "MainLayer.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "imgui/imgui.h"

#include "VoxelEngine/Events/ApplicationEvent.h"
#include "VoxelEngine/Events/MouseEvent.h"

MainLayer::MainLayer()
	: Layer("MainLayer"), m_CameraController(16.f / 9.f)
{
}

void MainLayer::OnAttach()
{
	m_VertexArray = VoxelEngine::VertexArray::Create();

	float Vertices[5 * 36] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f };

	VoxelEngine::Ref<VoxelEngine::VertexBuffer> VertexBuffer;
	VertexBuffer.reset(VoxelEngine::VertexBuffer::Create(Vertices, sizeof(Vertices)));
	VertexBuffer->SetLayout({
		{ VoxelEngine::ShaderDataType::Float3, "a_Position" },
		{ VoxelEngine::ShaderDataType::Float2, "a_TexCoord" }
		});

	m_VertexArray->AddVertexBuffer(VertexBuffer);

	uint32_t Indices[36] = {
		// front
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35
	};
	VoxelEngine::Ref<VoxelEngine::IndexBuffer> IndexBuffer;
	IndexBuffer.reset(VoxelEngine::IndexBuffer::Create(Indices, sizeof(Indices) / sizeof(uint32_t)));
	m_VertexArray->SetIndexBuffer(IndexBuffer);

	m_Shader = VoxelEngine::Shader::Create("assets/shaders/Texture.glsl");

	m_Texture = VoxelEngine::Texure2D::Create("assets/textures/Stone.png");

	std::dynamic_pointer_cast<VoxelEngine::OpenGLShader>(m_Shader)->Bind();
	std::dynamic_pointer_cast<VoxelEngine::OpenGLShader>(m_Shader)->UploadUniformInt("u_Texture", 0);
}


void MainLayer::OnDetach()
{
}

void MainLayer::OnUpdate(VoxelEngine::Timestep ts)
{
	m_CameraController.OnUpdate(ts);

	VoxelEngine::RenderCommand::SetClearColor({ 0.1, 0.1, 0.1, 1 });
	VoxelEngine::RenderCommand::Clear();

	VoxelEngine::Renderer::BeginScene(m_CameraController.GetCamera());

	static glm::mat4 scale = glm::scale(glm::mat4(1.f), glm::vec3(1.f));

	glm::vec3 pos(0.f, 0.f, 0.f);
	glm::mat4 transform = glm::translate(glm::mat4(1.f), pos) * scale;

	m_Shader->Bind();
	m_Texture->Bind();

	VoxelEngine::Renderer::Submit(m_Shader, m_VertexArray, transform);

	VoxelEngine::Renderer::EndScene();
}

void MainLayer::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::Text("Fov: %f", m_CameraController.GetFOV());
	ImGui::End();
}

void MainLayer::OnEvent(VoxelEngine::Event& event)
{
	m_CameraController.OnEvent(event);
}
