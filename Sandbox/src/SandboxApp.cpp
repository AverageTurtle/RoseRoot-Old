#include <VoxelEngine.h>

#include "imgui/imgui.h"


class ExampleLayer : public VoxelEngine::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(45.f, 16.f/9.f, 0.01f, 100.0f), m_CubePos(0.f)
	{
		m_VertexArray.reset(VoxelEngine::VertexArray::Create());

		m_VertexArray.reset(VoxelEngine::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<VoxelEngine::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VoxelEngine::VertexBuffer::Create(vertices, sizeof(vertices)));
		VoxelEngine::BufferLayout layout = {
			{ VoxelEngine::ShaderDataType::Float3, "a_Position" },
			{ VoxelEngine::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<VoxelEngine::IndexBuffer> indexBuffer;
		indexBuffer.reset(VoxelEngine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(VoxelEngine::VertexArray::Create());

		float squareVertices[3 * 8] = {
			// front
			-1.0, -1.0,  1.0,
			 1.0, -1.0,  1.0,
			 1.0,  1.0,  1.0,
			-1.0,  1.0,  1.0,
			// back
			-1.0, -1.0, -1.0,
			 1.0, -1.0, -1.0,
			 1.0,  1.0, -1.0,
			-1.0,  1.0, -1.0
		};

		std::shared_ptr<VoxelEngine::VertexBuffer> squareVB;
		squareVB.reset(VoxelEngine::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ VoxelEngine::ShaderDataType::Float3, "a_Position" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[36] = {
									// front   // right
									0, 1, 2,   1, 5, 6,
									2, 3, 0,   6, 2, 1,							
									// back	   // left
									7, 6, 5,   4, 0, 3,
									5, 4, 7,   3, 7, 4,
									// bottom  // top
									4, 5, 1,   3, 2, 6,
									1, 0, 4,   6, 7, 3 };
		std::shared_ptr<VoxelEngine::IndexBuffer> squareIB;
		squareIB.reset(VoxelEngine::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

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

		m_Shader.reset(new VoxelEngine::Shader(vertexSrc, fragmentSrc));

		std::string purpleShaderVertexSrc = R"(
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

		std::string purpleShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			void main()
			{
				color = vec4(0.3, 0.1, 0.3, 1.0);
			}
		)";

		m_PurpleShader.reset(new VoxelEngine::Shader(purpleShaderVertexSrc, purpleShaderFragmentSrc));
		
		m_Camera.SetPosition(glm::vec3(10, 0, 0));
	}

	void OnUpdate(VoxelEngine::Timestep ts) override
	{
		//VE_TRACE("Delta time: {0}s ({1}ms)", ts.GetSeconds(), ts.GetMilliseconds());
		
		//move Camera
		float camSpeedTS = cameraSpeed * ts;
		if (VoxelEngine::Input::IsKeyPressed(VE_KEY_A))
		{
			cameraPos = cameraPos + glm::vec3(-camSpeedTS, 0.f, 0.f);
		}
		if (VoxelEngine::Input::IsKeyPressed(VE_KEY_D))
		{
			cameraPos = cameraPos + glm::vec3(camSpeedTS, 0.f, 0.f);
		}
		if (VoxelEngine::Input::IsKeyPressed(VE_KEY_W))
		{
			cameraPos = cameraPos + glm::vec3(0.f, 0.f, -camSpeedTS);
		}
		if (VoxelEngine::Input::IsKeyPressed(VE_KEY_S))
		{
			cameraPos = cameraPos + glm::vec3(0.f, 0.f, camSpeedTS);
		}

		if (VoxelEngine::Input::IsKeyPressed(VE_KEY_LEFT))
		{
			cameraRot = cameraRot + glm::vec3(0.f, cameraRotationSpeed*ts, 0);
		}
		if (VoxelEngine::Input::IsKeyPressed(VE_KEY_RIGHT))
		{
			cameraRot = cameraRot + glm::vec3(0.f, -cameraRotationSpeed * ts, 0);
		}


		//Move Cube
		if (VoxelEngine::Input::IsKeyPressed(VE_KEY_J))
		{
			m_CubePos = m_CubePos + glm::vec3(-cubeSpeed * ts, 0.f, 0.f);
		}
		if (VoxelEngine::Input::IsKeyPressed(VE_KEY_L))
		{
			m_CubePos = m_CubePos + glm::vec3(cubeSpeed * ts, 0.f, 0.f);
		}
		if (VoxelEngine::Input::IsKeyPressed(VE_KEY_I))
		{
			m_CubePos = m_CubePos + glm::vec3(0.f, 0.f, -cubeSpeed * ts);
		}
		if (VoxelEngine::Input::IsKeyPressed(VE_KEY_K))
		{
			m_CubePos = m_CubePos + glm::vec3(0.f, 0.f, cubeSpeed * ts);
		}


		VoxelEngine::RenderCommand::SetClearColor({ 0.1, 0.1, 0.1, 1 });
		VoxelEngine::RenderCommand::Clear();

		m_Camera.SetPosition(cameraPos);
		m_Camera.SetRotation(cameraRot);

		VoxelEngine::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.f), glm::vec3(0.5f));

		for (int z = 0; z < 20; z++)
		{
			for (int x = 0; x < 20; x++)
			{
				for (int y = 0; y < 2; y++)
				{
					glm::vec3 pos(x * 3.f, y * 3.f, z * -3.f);
					glm::mat4 transform = glm::translate(glm::mat4(1.f), m_CubePos + pos) * scale;
					VoxelEngine::Renderer::Submit(m_PurpleShader, m_SquareVA, transform);
				}
			}
		}

		//VoxelEngine::Renderer::Submit(m_Shader, m_VertexArray);

		VoxelEngine::Renderer::EndScene();

		//VE_TRACE("{0}, {1}, {2}", m_Camera.GetPosition().x, m_Camera.GetPosition().y, m_Camera.GetPosition().z);
	}
	

	virtual void OnImGuiRender() override
	{
	}

	void OnEvent(VoxelEngine::Event& event) override
	{
	}

	private:
		float cameraSpeed = 5.f;
		float cameraRotationSpeed = 120.f;
		glm::vec3 cameraRot = glm::vec3(0.f, 0.f, 0.f);
		glm::vec3 cameraPos = glm::vec3(0.f, 0.f, 2.f);

		std::shared_ptr<VoxelEngine::Shader> m_Shader;
		std::shared_ptr<VoxelEngine::VertexArray> m_VertexArray;

		std::shared_ptr<VoxelEngine::Shader> m_PurpleShader;
		std::shared_ptr<VoxelEngine::VertexArray> m_SquareVA;

		VoxelEngine::PerspectiveCamera m_Camera;

		glm::vec3 m_CubePos;
		float cubeSpeed = 1.f;
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