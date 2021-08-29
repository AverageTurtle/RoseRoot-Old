#pragma once

#include "Core.h"

namespace VoxelEngine {

	class VOXELENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}