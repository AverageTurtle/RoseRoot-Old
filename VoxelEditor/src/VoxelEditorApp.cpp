#pragma once
#include <VoxelEngine.h>
//---Entry Point---
#include <VoxelEngine/Core/EntryPoint.h>
//-----------------

#include "EditorLayer.h"

namespace VoxelEngine {
	class VoxelEditor : public Application
	{
	public:
		VoxelEditor()
			: Application("Voxel Editor")
		{
			PushLayer(new EditorLayer(GetWindow()));
		}

		~VoxelEditor()
		{

		}
	};

	Application* CreateApplication()
	{
		return new VoxelEditor();
	}
}
