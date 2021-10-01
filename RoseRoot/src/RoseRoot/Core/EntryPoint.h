#pragma once

#ifdef RR_PLATFORM_WINDOWS 

extern RoseRoot::Application* RoseRoot::CreateApplication();

int main(int argc, char** argv)
{
	RoseRoot::Log::Init();

	RR_PROFILE_BEGIN_SESSION("Startup", "VoxelEngineProfile-Startup.json");
	auto app = RoseRoot::CreateApplication();
	RR_PROFILE_END_SESSION();

	RR_PROFILE_BEGIN_SESSION("Runtime", "VoxelEngineProfile-Runtime.json");
	app->Run();
	RR_PROFILE_END_SESSION();

	RR_PROFILE_BEGIN_SESSION("Shutdown", "VoxelEngineProfile-Shutdown.json");
	delete app;
	RR_PROFILE_END_SESSION();
}

#endif