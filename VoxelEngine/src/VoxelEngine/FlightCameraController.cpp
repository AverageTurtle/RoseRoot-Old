#include "vepch.h"
#include "FlightCameraController.h"

#include "VoxelEngine/Core/Input.h"
#include "VoxelEngine/Core/KeyCodes.h"


namespace VoxelEngine {

	FlightCameraController::FlightCameraController(float aspectRatio)
		: m_AspectRatio(aspectRatio), m_Camera(m_FOV, m_AspectRatio, 0.01f, 1000.0f)
	{
	}

	void FlightCameraController::OnUpdate(Timestep ts)
	{
		float camSpeedTS = m_CameraSpeed * ts;

		if (Input::IsKeyPressed(VE_KEY_W))
			m_CameraPosition += camSpeedTS * m_Camera.GetFront();
		if (Input::IsKeyPressed(VE_KEY_S))
			m_CameraPosition -= camSpeedTS * m_Camera.GetFront();

		if (Input::IsKeyPressed(VE_KEY_A))
			m_CameraPosition -= camSpeedTS * m_Camera.GetRight();
		if (Input::IsKeyPressed(VE_KEY_D))
			m_CameraPosition += camSpeedTS * m_Camera.GetRight();


		if (m_FirstMouse)
		{
			m_LastX = Input::GetMouseX();
			m_LastY = Input::GetMouseY();
			m_FirstMouse = false;
		}

		float xoffset = Input::GetMouseX() - m_LastX;
		float yoffset = m_LastY - Input::GetMouseY();
		m_LastX = Input::GetMouseX();
		m_LastY = Input::GetMouseY();

		xoffset *= m_CameraSensitivity * ts;
		yoffset *= m_CameraSensitivity * ts;

		m_CameraYaw   += xoffset;
		m_CameraPitch += yoffset;

		if (m_CameraPitch > 89.0f)
			m_CameraPitch = 89.0f;
		if (m_CameraPitch < -89.0f)
			m_CameraPitch = -89.0f;

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetYaw(m_CameraYaw);
		m_Camera.SetPitch(m_CameraPitch);
	}

	void FlightCameraController::OnEvent(Event& e)
	{
		VoxelEngine::EventDispatcher dispatcher(e);
		dispatcher.Dispatch<VoxelEngine::MouseScrolledEvent>(VE_BIND_EVENT_FN(FlightCameraController::OnMouseScrolled));
		dispatcher.Dispatch<VoxelEngine::WindowResizeEvent> (VE_BIND_EVENT_FN(FlightCameraController::OnWindowResized));
	}

	bool FlightCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_FOV -= e.GetYOffset();

		if (m_FOV > 90)
			m_FOV = 90;
		if (m_FOV < 1)
			m_FOV = 1;
		m_Camera.SetFOV(m_FOV);
		return false;
	}

	bool FlightCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		m_Camera.SetAspectRatio((float)e.GetWidth() / (float)e.GetHeight());
		return false;
	}

}


