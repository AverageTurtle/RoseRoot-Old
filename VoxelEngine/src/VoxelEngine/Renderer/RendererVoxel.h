#pragma once

#include "Camera.h"
#include "Texture.h"

namespace VoxelEngine {

	class RendererVoxel
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const PerspectiveCamera& camera);
		static void EndScene();

		// Primitives
		static void DrawQuad(const glm::vec3& position, const glm::vec3& scale, const glm::vec3& rotation, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec3& scale, const glm::vec3& rotation, const glm::vec4& color, const Ref<Texure2D>& texture);
	};
}