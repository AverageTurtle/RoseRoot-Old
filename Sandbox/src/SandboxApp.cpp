#include <VoxelEngine.h>

class Sandbox : public VoxelEngine::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}

};

VoxelEngine::Application* VoxelEngine::CreateApplication()
{
	return new Sandbox();
}