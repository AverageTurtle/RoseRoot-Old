#include "vepch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace VoxelEngine {

	Ref<Texure2D> Texure2D::Create(uint32_t width, uint32_t height)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    VE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLTexture2D>(width, height);
		}

		VE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
		return Ref<Texure2D>();
	}

	Ref<Texure2D> Texure2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    VE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLTexture2D>(path);
		}

		VE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
		return Ref<Texure2D>();
	}
}