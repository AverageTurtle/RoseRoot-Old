#pragma once

namespace RoseRoot {
typedef enum class KeyCode : uint16_t
{
	// From glfw3.h
	Space = 32,
	Apostrophe = 39, /* ' */
	Comma = 44, /* , */
	Minus = 45, /* - */
	Period = 46, /* . */
	Slash = 47, /* / */

	D0 = 48, /* 0 */
	D1 = 49, /* 1 */
	D2 = 50, /* 2 */
	D3 = 51, /* 3 */
	D4 = 52, /* 4 */
	D5 = 53, /* 5 */
	D6 = 54, /* 6 */
	D7 = 55, /* 7 */
	D8 = 56, /* 8 */
	D9 = 57, /* 9 */

	Semicolon = 59, /* ; */
	Equal = 61, /* = */

	A = 65,
	B = 66,
	C = 67,
	D = 68,
	E = 69,
	F = 70,
	G = 71,
	H = 72,
	I = 73,
	J = 74,
	K = 75,
	L = 76,
	M = 77,
	N = 78,
	O = 79,
	P = 80,
	Q = 81,
	R = 82,
	S = 83,
	T = 84,
	U = 85,
	V = 86,
	W = 87,
	X = 88,
	Y = 89,
	Z = 90,

	LeftBracket = 91,  /* [ */
	Backslash = 92,  /* \ */
	RightBracket = 93,  /* ] */
	GraveAccent = 96,  /* ` */

	World1 = 161, /* non-US #1 */
	World2 = 162, /* non-US #2 */

	/* Function keys */
	Escape = 256,
	Enter = 257,
	Tab = 258,
	Backspace = 259,
	Insert = 260,
	Delete = 261,
	Right = 262,
	Left = 263,
	Down = 264,
	Up = 265,
	PageUp = 266,
	PageDown = 267,
	Home = 268,
	End = 269,
	CapsLock = 280,
	ScrollLock = 281,
	NumLock = 282,
	PrintScreen = 283,
	Pause = 284,
	F1 = 290,
	F2 = 291,
	F3 = 292,
	F4 = 293,
	F5 = 294,
	F6 = 295,
	F7 = 296,
	F8 = 297,
	F9 = 298,
	F10 = 299,
	F11 = 300,
	F12 = 301,
	F13 = 302,
	F14 = 303,
	F15 = 304,
	F16 = 305,
	F17 = 306,
	F18 = 307,
	F19 = 308,
	F20 = 309,
	F21 = 310,
	F22 = 311,
	F23 = 312,
	F24 = 313,
	F25 = 314,

	/* Keypad */
	KP0 = 320,
	KP1 = 321,
	KP2 = 322,
	KP3 = 323,
	KP4 = 324,
	KP5 = 325,
	KP6 = 326,
	KP7 = 327,
	KP8 = 328,
	KP9 = 329,
	KPDecimal = 330,
	KPDivide = 331,
	KPMultiply = 332,
	KPSubtract = 333,
	KPAdd = 334,
	KPEnter = 335,
	KPEqual = 336,

	LeftShift = 340,
	LeftControl = 341,
	LeftAlt = 342,
	LeftSuper = 343,
	RightShift = 344,
	RightControl = 345,
	RightAlt = 346,
	RightSuper = 347,
	Menu = 348
} Key;

inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
{
	os << static_cast<int32_t>(keyCode);
	return os;
}
}
// From glfw3.h
#define RR_KEY_SPACE           ::RoseRoot::Key::Space
#define RR_KEY_APOSTROPHE      ::RoseRoot::Key::Apostrophe    /* ' */
#define RR_KEY_COMMA           ::RoseRoot::Key::Comma         /* , */
#define RR_KEY_MINUS           ::RoseRoot::Key::Minus         /* - */
#define RR_KEY_PERIOD          ::RoseRoot::Key::Period        /* . */
#define RR_KEY_SLASH           ::RoseRoot::Key::Slash         /* / */
#define RR_KEY_0               ::RoseRoot::Key::D0
#define RR_KEY_1               ::RoseRoot::Key::D1
#define RR_KEY_2               ::RoseRoot::Key::D2
#define RR_KEY_3               ::RoseRoot::Key::D3
#define RR_KEY_4               ::RoseRoot::Key::D4
#define RR_KEY_5               ::RoseRoot::Key::D5
#define RR_KEY_6               ::RoseRoot::Key::D6
#define RR_KEY_7               ::RoseRoot::Key::D7
#define RR_KEY_8               ::RoseRoot::Key::D8
#define RR_KEY_9               ::RoseRoot::Key::D9
#define RR_KEY_SEMICOLON       ::RoseRoot::Key::Semicolon     /* ; */
#define RR_KEY_EQUAL           ::RoseRoot::Key::Equal         /* = */
#define RR_KEY_A               ::RoseRoot::Key::A
#define RR_KEY_B               ::RoseRoot::Key::B
#define RR_KEY_C               ::RoseRoot::Key::C
#define RR_KEY_D               ::RoseRoot::Key::D
#define RR_KEY_E               ::RoseRoot::Key::E
#define RR_KEY_F               ::RoseRoot::Key::F
#define RR_KEY_G               ::RoseRoot::Key::G
#define RR_KEY_H               ::RoseRoot::Key::H
#define RR_KEY_I               ::RoseRoot::Key::I
#define RR_KEY_J               ::RoseRoot::Key::J
#define RR_KEY_K               ::RoseRoot::Key::K
#define RR_KEY_L               ::RoseRoot::Key::L
#define RR_KEY_M               ::RoseRoot::Key::M
#define RR_KEY_N               ::RoseRoot::Key::N
#define RR_KEY_O               ::RoseRoot::Key::O
#define RR_KEY_P               ::RoseRoot::Key::P
#define RR_KEY_Q               ::RoseRoot::Key::Q
#define RR_KEY_R               ::RoseRoot::Key::R
#define RR_KEY_S               ::RoseRoot::Key::S
#define RR_KEY_T               ::RoseRoot::Key::T
#define RR_KEY_U               ::RoseRoot::Key::U
#define RR_KEY_V               ::RoseRoot::Key::V
#define RR_KEY_W               ::RoseRoot::Key::W
#define RR_KEY_X               ::RoseRoot::Key::X
#define RR_KEY_Y               ::RoseRoot::Key::Y
#define RR_KEY_Z               ::RoseRoot::Key::Z
#define RR_KEY_LEFT_BRACKET    ::RoseRoot::Key::LeftBracket   /* [ */
#define RR_KEY_BACKSLASH       ::RoseRoot::Key::Backslash     /* \ */
#define RR_KEY_RIGHT_BRACKET   ::RoseRoot::Key::RightBracket  /* ] */
#define RR_KEY_GRAVE_ACCENT    ::RoseRoot::Key::GraveAccent   /* ` */
#define RR_KEY_WORLD_1         ::RoseRoot::Key::World1        /* non-US #1 */
#define RR_KEY_WORLD_2         ::RoseRoot::Key::World2        /* non-US #2 */
								 			 
/* Function keys */				 			 
#define RR_KEY_ESCAPE          ::RoseRoot::Key::Escape
#define RR_KEY_ENTER           ::RoseRoot::Key::Enter
#define RR_KEY_TAB             ::RoseRoot::Key::Tab
#define RR_KEY_BACKSPACE       ::RoseRoot::Key::Backspace
#define RR_KEY_INSERT          ::RoseRoot::Key::Insert
#define RR_KEY_DELETE          ::RoseRoot::Key::Delete
#define RR_KEY_RIGHT           ::RoseRoot::Key::Right
#define RR_KEY_LEFT            ::RoseRoot::Key::Left
#define RR_KEY_DOWN            ::RoseRoot::Key::Down
#define RR_KEY_UP              ::RoseRoot::Key::Up
#define RR_KEY_PAGE_UP         ::RoseRoot::Key::PageUp
#define RR_KEY_PAGE_DOWN       ::RoseRoot::Key::PageDown
#define RR_KEY_HOME            ::RoseRoot::Key::Home
#define RR_KEY_END             ::RoseRoot::Key::End
#define RR_KEY_CAPS_LOCK       ::RoseRoot::Key::CapsLock
#define RR_KEY_SCROLL_LOCK     ::RoseRoot::Key::ScrollLock
#define RR_KEY_NUM_LOCK        ::RoseRoot::Key::NumLock
#define RR_KEY_PRINT_SCREEN    ::RoseRoot::Key::PrintScreen
#define RR_KEY_PAUSE           ::RoseRoot::Key::Pause
#define RR_KEY_F1              ::RoseRoot::Key::F1
#define RR_KEY_F2              ::RoseRoot::Key::F2
#define RR_KEY_F3              ::RoseRoot::Key::F3
#define RR_KEY_F4              ::RoseRoot::Key::F4
#define RR_KEY_F5              ::RoseRoot::Key::F5
#define RR_KEY_F6              ::RoseRoot::Key::F6
#define RR_KEY_F7              ::RoseRoot::Key::F7
#define RR_KEY_F8              ::RoseRoot::Key::F8
#define RR_KEY_F9              ::RoseRoot::Key::F9
#define RR_KEY_F10             ::RoseRoot::Key::F10
#define RR_KEY_F11             ::RoseRoot::Key::F11
#define RR_KEY_F12             ::RoseRoot::Key::F12
#define RR_KEY_F13             ::RoseRoot::Key::F13
#define RR_KEY_F14             ::RoseRoot::Key::F14
#define RR_KEY_F15             ::RoseRoot::Key::F15
#define RR_KEY_F16             ::RoseRoot::Key::F16
#define RR_KEY_F17             ::RoseRoot::Key::F17
#define RR_KEY_F18             ::RoseRoot::Key::F18
#define RR_KEY_F19             ::RoseRoot::Key::F19
#define RR_KEY_F20             ::RoseRoot::Key::F20
#define RR_KEY_F21             ::RoseRoot::Key::F21
#define RR_KEY_F22             ::RoseRoot::Key::F22
#define RR_KEY_F23             ::RoseRoot::Key::F23
#define RR_KEY_F24             ::RoseRoot::Key::F24
#define RR_KEY_F25             ::RoseRoot::Key::F25
								 			 
/* Keypad */					 			 
#define RR_KEY_KP_0            ::RoseRoot::Key::KP0
#define RR_KEY_KP_1            ::RoseRoot::Key::KP1
#define RR_KEY_KP_2            ::RoseRoot::Key::KP2
#define RR_KEY_KP_3            ::RoseRoot::Key::KP3
#define RR_KEY_KP_4            ::RoseRoot::Key::KP4
#define RR_KEY_KP_5            ::RoseRoot::Key::KP5
#define RR_KEY_KP_6            ::RoseRoot::Key::KP6
#define RR_KEY_KP_7            ::RoseRoot::Key::KP7
#define RR_KEY_KP_8            ::RoseRoot::Key::KP8
#define RR_KEY_KP_9            ::RoseRoot::Key::KP9
#define RR_KEY_KP_DECIMAL      ::RoseRoot::Key::KPDecimal
#define RR_KEY_KP_DIVIDE       ::RoseRoot::Key::KPDivide
#define RR_KEY_KP_MULTIPLY     ::RoseRoot::Key::KPMultiply
#define RR_KEY_KP_SUBTRACT     ::RoseRoot::Key::KPSubtract
#define RR_KEY_KP_ADD          ::RoseRoot::Key::KPAdd
#define RR_KEY_KP_ENTER        ::RoseRoot::Key::KPEnter
#define RR_KEY_KP_EQUAL        ::RoseRoot::Key::KPEqual
								 			 
#define RR_KEY_LEFT_SHIFT      ::RoseRoot::Key::LeftShift
#define RR_KEY_LEFT_CONTROL    ::RoseRoot::Key::LeftControl
#define RR_KEY_LEFT_ALT        ::RoseRoot::Key::LeftAlt
#define RR_KEY_LEFT_SUPER      ::RoseRoot::Key::LeftSuper
#define RR_KEY_RIGHT_SHIFT     ::RoseRoot::Key::RightShift
#define RR_KEY_RIGHT_CONTROL   ::RoseRoot::Key::RightControl
#define RR_KEY_RIGHT_ALT       ::RoseRoot::Key::RightAlt
#define RR_KEY_RIGHT_SUPER     ::RoseRoot::Key::RightSuper
#define RR_KEY_MENU            ::RoseRoot::Key::Menu