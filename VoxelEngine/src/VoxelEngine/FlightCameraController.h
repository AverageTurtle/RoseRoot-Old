#pragma once

#include "VoxelEngine/Renderer/Camera.h"
#include "VoxelEngine/Core/Timestep.h"

#include "VoxelEngine/Events/ApplicationEvent.h"
#include "VoxelEngine/Events/MouseEvent.h"
#include "VoxelEngine/Events/KeyEvent.h"

#include "VoxelEngine/Core/Window.h"

namespace VoxelEngine {
	class FlightCameraController
	{
	public:
		FlightCameraController(float aspectRatio);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		PerspectiveCamera& GetCamera() { return m_Camera; }
		const PerspectiveCamera& GetCamera() const { return m_Camera; }

		float GetFOV() const { return m_FOV; }
		void SetFOV(float level) { m_FOV = level; }

		float GetAspectRatio() const { return m_AspectRatio; }
		void SetAspectRatio(float ratio) { m_AspectRatio = ratio; m_Camera.SetAspectRatio(m_AspectRatio); }

		float GetSensitivity() const { return m_CameraSensitivity; }
		void SetSensitivity(float sensitivity) { m_CameraSensitivity = sensitivity; }

		void SetTracking(bool tracking) { m_Tracking = tracking; m_FirstMouse = tracking; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
	private:
		bool m_Tracking = true;
		float m_AspectRatio;
		float m_FOV = 45.0f;
		PerspectiveCamera m_Camera;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraYaw = -90.f, m_CameraPitch = 0.f;
		float m_CameraSpeed = 5.f, m_CameraSensitivity = 20.f;

		bool m_FirstMouse = true;
		float m_LastX = 0.f, m_LastY = 0.f;
	};
}