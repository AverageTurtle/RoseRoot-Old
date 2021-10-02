#pragma once
#include <RoseRoot.h>
//---Entry Point---
#include <RoseRoot/Core/EntryPoint.h>
//-----------------

#include "EditorLayer.h"

namespace RoseRoot {
	class RoseStem : public Application
	{
	public:
		RoseStem()
			: Application("Rose Stem")
		{
			PushLayer(new EditorLayer());
		}

		~RoseStem()
		{

		}
	};

	Application* CreateApplication()
	{
		return new RoseStem();
	}
}
