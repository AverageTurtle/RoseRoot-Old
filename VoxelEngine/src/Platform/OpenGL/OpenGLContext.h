#pragma once

#include "VoxelEngine/Renderer/GraphicsContexted.h"


struct GLFWwindow;

namespace VoxelEngine {

	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_windowHandle;
	};
}