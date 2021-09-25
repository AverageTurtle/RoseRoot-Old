#include <VoxelEngine.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public VoxelEngine::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(45.f, 16.f / 9.f, 0.01f, 1000.0f)
	{
		m_VertexArray.reset(VoxelEngine::VertexArray::Create());

		m_VertexArray.reset(VoxelEngine::VertexArray::Create());

		float vertices[4 * 7] = {
			 -0.5f,  1.0f,    0.5f,   0.0f,  0.0f,
			 57.5f,  1.0f,    0.5f,  30.0f,  0.0f,
			 57.5f,  1.0f,  -57.5f,  30.0f, 30.0f,
			 -0.5f,  1.0f,  -57.5f,   0.0f, 30.0f,
		};

		VoxelEngine::Ref<VoxelEngine::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VoxelEngine::VertexBuffer::Create(vertices, sizeof(vertices)));
		VoxelEngine::BufferLayout layout = {
			{ VoxelEngine::ShaderDataType::Float3, "a_Position" },
			{ VoxelEngine::ShaderDataType::Float2, "a_TexCoord" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };
		VoxelEngine::Ref<VoxelEngine::IndexBuffer> indexBuffer;
		indexBuffer.reset(VoxelEngine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_CubeVA.reset(VoxelEngine::VertexArray::Create());

		float cubeVertices[5 * 36] = {
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

		VoxelEngine::Ref<VoxelEngine::VertexBuffer> cubeVB;
		cubeVB.reset(VoxelEngine::VertexBuffer::Create(cubeVertices , sizeof(cubeVertices)));
		cubeVB->SetLayout({
			{ VoxelEngine::ShaderDataType::Float3, "a_Position" },
			{ VoxelEngine::ShaderDataType::Float2, "a_TexCoord" }
			});

		m_CubeVA->AddVertexBuffer(cubeVB);


		uint32_t cubeIndices[36] = {
			// front
			0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35
			};
		VoxelEngine::Ref<VoxelEngine::IndexBuffer> cubeIB;
		cubeIB.reset(VoxelEngine::IndexBuffer::Create(cubeIndices, sizeof(cubeIndices) / sizeof(uint32_t)));
		m_CubeVA->SetIndexBuffer(cubeIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			out vec3 v_Position;
			out vec4 v_Color;
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			in vec4 v_Color;
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader = VoxelEngine::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			uniform vec3 u_Color;
			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_FlatColorShader = VoxelEngine::Shader::Create("FlatColorShader", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);

		auto textureShader = m_ShaderLibary.Load("assets/shaders/Texture.glsl");

		m_Texture = VoxelEngine::Texure2D::Create("assets/textures/Stone.png");
		m_GlassTexture = VoxelEngine::Texure2D::Create("assets/textures/Glass.png");

		std::dynamic_pointer_cast<VoxelEngine::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<VoxelEngine::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(VoxelEngine::Timestep ts) override
	{
		//VE_TRACE("Delta time: {0}s ({1}ms)", ts.GetSeconds(), ts.GetMilliseconds());

		//move Camera
		float camSpeedTS = cameraSpeed * ts;
		if (VoxelEngine::Input::IsKeyPressed(VE_KEY_A))
			cameraPos = cameraPos + glm::vec3(-camSpeedTS, 0.f, 0.f);
		if (VoxelEngine::Input::IsKeyPressed(VE_KEY_D))
			cameraPos = cameraPos + glm::vec3(camSpeedTS, 0.f, 0.f);
		if (VoxelEngine::Input::IsKeyPressed(VE_KEY_W))
			cameraPos = cameraPos + glm::vec3(0.f, 0.f, -camSpeedTS);
		if (VoxelEngine::Input::IsKeyPressed(VE_KEY_S))
			cameraPos = cameraPos + glm::vec3(0.f, 0.f, camSpeedTS);

		if (VoxelEngine::Input::IsKeyPressed(VE_KEY_LEFT))
			cameraRot = cameraRot + glm::vec3(0.f, cameraRotationSpeed * ts, 0);
		if (VoxelEngine::Input::IsKeyPressed(VE_KEY_RIGHT))
			cameraRot = cameraRot + glm::vec3(0.f, -cameraRotationSpeed * ts, 0);


		VoxelEngine::RenderCommand::SetClearColor({ 0.1, 0.1, 0.1, 1 });
		VoxelEngine::RenderCommand::Clear();

		m_Camera.SetPosition(cameraPos);
		m_Camera.SetRotation(cameraRot);

		VoxelEngine::Renderer::BeginScene(m_Camera);

		static glm::mat4 scale = glm::scale(glm::mat4(1.f), glm::vec3(1.f));

		m_Texture->Bind();

		std::dynamic_pointer_cast<VoxelEngine::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<VoxelEngine::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_CubeColor);

		for (int z = 0; z < 20; z++)
		{
			for (int x = 0; x < 20; x++)
			{
				for (int y = 0; y < 3; y++)
				{
					glm::vec3 pos(x * 3.f, y * 3.f, z * -3.f);
					glm::mat4 transform = glm::translate(glm::mat4(1.f), pos) * scale;
					VoxelEngine::Renderer::Submit(m_FlatColorShader, m_CubeVA, transform);
				}
			}
		}

		auto textureShader = m_ShaderLibary.Get("Texture");

		{
			glm::vec3 pos(-3.f, 0.f, 0.f);
			glm::mat4 transform = glm::translate(glm::mat4(1.f), pos) * scale;
			m_Texture->Bind();
			VoxelEngine::Renderer::Submit(textureShader, m_CubeVA, transform);
		}
		{
			glm::mat4 transform = glm::translate(glm::mat4(1.f), glm::vec3(0.f, -1.5f, 0.f));
			m_Texture->Bind();
			VoxelEngine::Renderer::Submit(textureShader, m_VertexArray, transform);
		}	
		{
			glm::vec3 pos(-6.f, 0.f, 0.f);
			glm::mat4 transform = glm::translate(glm::mat4(1.f), pos) * scale;
			m_GlassTexture->Bind();
			VoxelEngine::Renderer::Submit(textureShader, m_CubeVA, transform);
		}
		VoxelEngine::Renderer::EndScene();
		//VE_TRACE("{0}, {1}, {2}", m_Camera.GetPosition().x, m_Camera.GetPosition().y, m_Camera.GetPosition().z);
	}


	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Cube Color", glm::value_ptr(m_CubeColor));
		ImGui::End();
	}

	void OnEvent(VoxelEngine::Event& event) override
	{
	}

private:
	float cameraSpeed = 5.f;
	float cameraRotationSpeed = 180.f;
	glm::vec3 cameraRot = glm::vec3(0.f, 0.f, 0.f);
	glm::vec3 cameraPos = glm::vec3(0.f, 0.f, 2.f);

	VoxelEngine::ShaderLibrary m_ShaderLibary;
	VoxelEngine::Ref<VoxelEngine::Shader> m_Shader;
	VoxelEngine::Ref<VoxelEngine::VertexArray> m_VertexArray;
				 
	VoxelEngine::Ref<VoxelEngine::Shader> m_FlatColorShader;
	VoxelEngine::Ref<VoxelEngine::VertexArray> m_CubeVA;

	VoxelEngine::Ref<VoxelEngine::Texure2D> m_Texture, m_GlassTexture;

	VoxelEngine::PerspectiveCamera m_Camera;

	glm::vec3 m_CubeColor = { 0.8, 0.2, 0.8 };
};

class Sandbox : public VoxelEngine::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}

};

VoxelEngine::Application* VoxelEngine::CreateApplication()
{
	return new Sandbox();
}