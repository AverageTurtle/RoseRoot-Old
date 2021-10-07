#include "rrpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace RoseRoot {

	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();
}