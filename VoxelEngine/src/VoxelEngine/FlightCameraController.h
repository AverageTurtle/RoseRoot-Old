#pragma once

#include "VoxelEngine/Renderer/Camera.h"
#include "VoxelEngine/Core/Timestep.h"

#include "VoxelEngine/Events/ApplicationEvent.h"
#include "VoxelEngine/Events/MouseEvent.h"

namespace VoxelEngine {
	class FlightCameraController
	{
	public:
		FlightCameraController(float aspectRatio);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		FPCamera& GetCamera() { return m_Camera; }
		const FPCamera& GetCamera() const { return m_Camera; }

		float GetFOV() const { return m_FOV; }
		void SetFOV(float level) { m_FOV = level; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		float m_AspectRatio;
		float m_FOV = 45.0f;
		FPCamera m_Camera;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraYaw = -90.f, m_CameraPitch = 0.f;
		float m_CameraSpeed = 5.f, m_CameraSensitivity = 90.f;

		bool m_FirstMouse = true;
		float m_LastX = 0.f, m_LastY = 0.f;
	};
}