#pragma once

#ifdef RR_PLATFORM_WINDOWS 

extern RoseRoot::Application* RoseRoot::CreateApplication(ApplicationCommandLineArgs args);

int main(int argc, char** argv)
{
	RoseRoot::Log::Init();

	RR_PROFILE_BEGIN_SESSION("Startup", "RoseProfile-Startup.json");
	auto app = RoseRoot::CreateApplication({ argc, argv });
	RR_PROFILE_END_SESSION();

	RR_PROFILE_BEGIN_SESSION("Runtime", "RoseProfile-Runtime.json");
	app->Run();
	RR_PROFILE_END_SESSION();

	RR_PROFILE_BEGIN_SESSION("Shutdown", "RoseProfile-Shutdown.json");
	delete app;
	RR_PROFILE_END_SESSION();
}

#endif