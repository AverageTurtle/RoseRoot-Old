#pragma once

namespace RoseRoot
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
#define RR_MOUSE_BUTTON_0      ::RoseRoot::Mouse::Button0
#define RR_MOUSE_BUTTON_1      ::RoseRoot::Mouse::Button1
#define RR_MOUSE_BUTTON_2      ::RoseRoot::Mouse::Button2
#define RR_MOUSE_BUTTON_3      ::RoseRoot::Mouse::Button3
#define RR_MOUSE_BUTTON_4      ::RoseRoot::Mouse::Button4
#define RR_MOUSE_BUTTON_5      ::RoseRoot::Mouse::Button5
#define RR_MOUSE_BUTTON_6      ::RoseRoot::Mouse::Button6
#define RR_MOUSE_BUTTON_7      ::RoseRoot::Mouse::Button7
#define RR_MOUSE_BUTTON_LAST   ::RoseRoot::Mouse::ButtonLast
#define RR_MOUSE_BUTTON_LEFT   ::RoseRoot::Mouse::ButtonLeft
#define RR_MOUSE_BUTTON_RIGHT  ::RoseRoot::Mouse::ButtonRight
#define RR_MOUSE_BUTTON_MIDDLE ::RoseRoot::Mouse::ButtonMiddle