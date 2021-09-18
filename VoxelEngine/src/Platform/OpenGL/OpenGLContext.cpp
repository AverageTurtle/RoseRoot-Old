#include "vepch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include "glad/glad.h"
#include <gl/GL.h>

namespace VoxelEngine {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_windowHandle(windowHandle)
	{
		VE_CORE_ASSERT(windowHandle, "Window handle is null!")
	}
	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_windowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		VE_CORE_ASSERT(status, "Failed to initailize Glad!");

		VE_CORE_INFO("OpenGL Info:");
		VE_CORE_INFO("Vendor: {0}", glGetString(GL_VENDOR));
		VE_CORE_INFO("Renderer: {0}", glGetString(GL_RENDERER));
		VE_CORE_INFO("Version: {0}", glGetString(GL_VERSION));
	}
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_windowHandle);
	}
}