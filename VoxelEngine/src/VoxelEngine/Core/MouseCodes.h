#pragma once

namespace VoxelEngine
{
	typedef enum class MouseCode : uint16_t
	{
		// From glfw3.h
		Button0 = 0,
		Button1 = 1,
		Button2 = 2,
		Button3 = 3,
		Button4 = 4,
		Button5 = 5,
		Button6 = 6,
		Button7 = 7,

		ButtonLast = Button7,
		ButtonLeft = Button0,
		ButtonRight = Button1,
		ButtonMiddle = Button2
	} Mouse;

	inline std::ostream& operator<<(std::ostream& os, MouseCode mouseCode)
	{
		os << static_cast<int32_t>(mouseCode);
		return os;
	}
}
//From glfw3.h
#define VE_MOUSE_BUTTON_0      ::VoxelEngine::Mouse::Button0
#define VE_MOUSE_BUTTON_1      ::VoxelEngine::Mouse::Button1
#define VE_MOUSE_BUTTON_2      ::VoxelEngine::Mouse::Button2
#define VE_MOUSE_BUTTON_3      ::VoxelEngine::Mouse::Button3
#define VE_MOUSE_BUTTON_4      ::VoxelEngine::Mouse::Button4
#define VE_MOUSE_BUTTON_5      ::VoxelEngine::Mouse::Button5
#define VE_MOUSE_BUTTON_6      ::VoxelEngine::Mouse::Button6
#define VE_MOUSE_BUTTON_7      ::VoxelEngine::Mouse::Button7
#define VE_MOUSE_BUTTON_LAST   ::VoxelEngine::Mouse::ButtonLast
#define VE_MOUSE_BUTTON_LEFT   ::VoxelEngine::Mouse::ButtonLeft
#define VE_MOUSE_BUTTON_RIGHT  ::VoxelEngine::Mouse::ButtonRight
#define VE_MOUSE_BUTTON_MIDDLE ::VoxelEngine::Mouse::ButtonMiddle