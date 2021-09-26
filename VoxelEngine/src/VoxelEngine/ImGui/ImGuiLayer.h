#pragma once

#include "VoxelEngine/Core/Layer.h"

#include "VoxelEngine/Events/KeyEvent.h"
#include "VoxelEngine/Events/MouseEvent.h"
#include "VoxelEngine/Events/ApplicationEvent.h"

namespace VoxelEngine {

	class VOXELENGINE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0;
	};
}