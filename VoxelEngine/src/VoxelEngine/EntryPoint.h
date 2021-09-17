#pragma once

#ifdef VE_PLATFORM_WINDOWS 

extern VoxelEngine::Application* VoxelEngine::CreateApplication();

int main(int argc, char** argv)
{
	VoxelEngine::Log::Init();
	VE_CORE_WARN("Initialized Log!");
	int a = 5;
	VE_CORE_INFO("Hello! Var={0}", a);

	auto app = VoxelEngine::CreateApplication();
	app->Run();
	delete app;
}

#endif