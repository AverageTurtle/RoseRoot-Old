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
		static void Flush();

		// Primitives
		static void DrawQuad(const glm::vec3& position, const glm::vec3& scale, const glm::vec3& rotation, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec3& scale, const glm::vec4& color, const Ref<Texture2D>& texture, float tiles = 1);
		static void DrawQuadRotated(const glm::vec3& position, const glm::vec3& scale, const glm::vec3& rotation, const glm::vec4& color, const Ref<Texture2D>& texture, float tiles = 1.f);
	};
}