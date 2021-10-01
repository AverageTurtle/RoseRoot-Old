#include "rrpch.h"
#include "FlightCameraController.h"

#include "RoseRoot/Core/Input.h"
#include "RoseRoot/Core/KeyCodes.h"


namespace RoseRoot {

	FlightCameraController::FlightCameraController(float aspectRatio)
		: m_AspectRatio(aspectRatio), m_Camera(m_FOV, m_AspectRatio, 0.01f, 1000.0f)
	{
	}

	void FlightCameraController::OnUpdate(Timestep ts)
	{
		RR_PROFILE_FUNCTION();

		float camSpeedTS = m_CameraSpeed * ts;

		if (Input::IsKeyPressed(RR_KEY_W))
			m_CameraPosition += camSpeedTS * m_Camera.GetFront();
		if (Input::IsKeyPressed(RR_KEY_S))
			m_CameraPosition -= camSpeedTS * m_Camera.GetFront();

		if (Input::IsKeyPressed(RR_KEY_A))
			m_CameraPosition -= camSpeedTS * m_Camera.GetRight();
		if (Input::IsKeyPressed(RR_KEY_D))
			m_CameraPosition += camSpeedTS * m_Camera.GetRight();

		if (Input::IsKeyPressed(RR_KEY_E))
			m_CameraPosition += camSpeedTS * m_Camera.GetUp();
		if (Input::IsKeyPressed(RR_KEY_Q))
			m_CameraPosition -= camSpeedTS * m_Camera.GetUp();

		if (Input::IsKeyPressed(RR_KEY_9))
			m_CameraSensitivity -= m_CameraSensitivity * ts;
		if (Input::IsKeyPressed(RR_KEY_0))
			m_CameraSensitivity += m_CameraSensitivity * ts;


		


		if (m_Tracking)
		{
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

			m_CameraYaw += xoffset;
			m_CameraPitch += yoffset;

			if (m_CameraPitch > 89.0f)
				m_CameraPitch = 89.0f;
			if (m_CameraPitch < -89.0f)
				m_CameraPitch = -89.0f;
			
			if (m_CameraYaw > 360.0f)
				m_CameraYaw = 0.f;
			if (m_CameraYaw < -360.0f)
				m_CameraYaw = 0.0f;
		}

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetYaw(m_CameraYaw);
		m_Camera.SetPitch(m_CameraPitch);
	}

	void FlightCameraController::OnEvent(Event& e)
	{
		RR_PROFILE_FUNCTION();

		RoseRoot::EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(RR_BIND_EVENT_FN(FlightCameraController::OnMouseScrolled));
	}

	bool FlightCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		RR_PROFILE_FUNCTION();

		m_FOV -= e.GetYOffset();

		if (m_FOV > 90)
			m_FOV = 90;
		if (m_FOV < 1)
			m_FOV = 1;
		m_Camera.SetFOV(m_FOV);
		return false;
	}
}


