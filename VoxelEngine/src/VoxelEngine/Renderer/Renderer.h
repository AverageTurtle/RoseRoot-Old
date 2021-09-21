#pragma once

#include "RenderCommand.h"

namespace VoxelEngine {

	class Renderer
	{
	public:
		static void BegineScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};
}