#include "rrpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace RoseRoot {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}