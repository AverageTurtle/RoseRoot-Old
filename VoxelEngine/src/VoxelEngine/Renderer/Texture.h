#pragma once

#include <string>

#include "VoxelEngine/Core/Core.h"

namespace VoxelEngine {

	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void SetData(void* data, uint32_t size) = 0;

		virtual void Bind(uint32_t slot = 0) const = 0;
	};

	class Texure2D : public Texture
	{
	public:
		static Ref<Texure2D> Create(uint32_t width, uint32_t height);
		static Ref<Texure2D> Create(const std::string& path);
	};
}