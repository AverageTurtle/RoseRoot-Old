#include "vepch.h"
#include "VoxelEngine/Core/Window.h"

#ifdef VE_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsWindow.h"
#endif

namespace VoxelEngine {
	Scope<Window> Window::Create(const WindowProps& props)
	{
#ifdef VE_PLATFORM_WINDOWS
		return CreateScope<WindowsWindow>(props);
#else
		VE_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
#endif
	}
}