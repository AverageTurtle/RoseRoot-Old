#pragma once

#include "VoxelEngine/Core/Layer.h"

#include "VoxelEngine/Events/KeyEvent.h"
#include "VoxelEngine/Events/MouseEvent.h"
#include "VoxelEngine/Events/ApplicationEvent.h"

namespace VoxelEngine {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e) override;

		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block; }
	private:
		bool m_BlockEvents = true;
		float m_Time = 0;
	};
}