#pragma once

namespace VoxelEngine {
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
#define VE_KEY_SPACE           ::VoxelEngine::Key::Space
#define VE_KEY_APOSTROPHE      ::VoxelEngine::Key::Apostrophe    /* ' */
#define VE_KEY_COMMA           ::VoxelEngine::Key::Comma         /* , */
#define VE_KEY_MINUS           ::VoxelEngine::Key::Minus         /* - */
#define VE_KEY_PERIOD          ::VoxelEngine::Key::Period        /* . */
#define VE_KEY_SLASH           ::VoxelEngine::Key::Slash         /* / */
#define VE_KEY_0               ::VoxelEngine::Key::D0
#define VE_KEY_1               ::VoxelEngine::Key::D1
#define VE_KEY_2               ::VoxelEngine::Key::D2
#define VE_KEY_3               ::VoxelEngine::Key::D3
#define VE_KEY_4               ::VoxelEngine::Key::D4
#define VE_KEY_5               ::VoxelEngine::Key::D5
#define VE_KEY_6               ::VoxelEngine::Key::D6
#define VE_KEY_7               ::VoxelEngine::Key::D7
#define VE_KEY_8               ::VoxelEngine::Key::D8
#define VE_KEY_9               ::VoxelEngine::Key::D9
#define VE_KEY_SEMICOLON       ::VoxelEngine::Key::Semicolon     /* ; */
#define VE_KEY_EQUAL           ::VoxelEngine::Key::Equal         /* = */
#define VE_KEY_A               ::VoxelEngine::Key::A
#define VE_KEY_B               ::VoxelEngine::Key::B
#define VE_KEY_C               ::VoxelEngine::Key::C
#define VE_KEY_D               ::VoxelEngine::Key::D
#define VE_KEY_E               ::VoxelEngine::Key::E
#define VE_KEY_F               ::VoxelEngine::Key::F
#define VE_KEY_G               ::VoxelEngine::Key::G
#define VE_KEY_H               ::VoxelEngine::Key::H
#define VE_KEY_I               ::VoxelEngine::Key::I
#define VE_KEY_J               ::VoxelEngine::Key::J
#define VE_KEY_K               ::VoxelEngine::Key::K
#define VE_KEY_L               ::VoxelEngine::Key::L
#define VE_KEY_M               ::VoxelEngine::Key::M
#define VE_KEY_N               ::VoxelEngine::Key::N
#define VE_KEY_O               ::VoxelEngine::Key::O
#define VE_KEY_P               ::VoxelEngine::Key::P
#define VE_KEY_Q               ::VoxelEngine::Key::Q
#define VE_KEY_R               ::VoxelEngine::Key::R
#define VE_KEY_S               ::VoxelEngine::Key::S
#define VE_KEY_T               ::VoxelEngine::Key::T
#define VE_KEY_U               ::VoxelEngine::Key::U
#define VE_KEY_V               ::VoxelEngine::Key::V
#define VE_KEY_W               ::VoxelEngine::Key::W
#define VE_KEY_X               ::VoxelEngine::Key::X
#define VE_KEY_Y               ::VoxelEngine::Key::Y
#define VE_KEY_Z               ::VoxelEngine::Key::Z
#define VE_KEY_LEFT_BRACKET    ::VoxelEngine::Key::LeftBracket   /* [ */
#define VE_KEY_BACKSLASH       ::VoxelEngine::Key::Backslash     /* \ */
#define VE_KEY_RIGHT_BRACKET   ::VoxelEngine::Key::RightBracket  /* ] */
#define VE_KEY_GRAVE_ACCENT    ::VoxelEngine::Key::GraveAccent   /* ` */
#define VE_KEY_WORLD_1         ::VoxelEngine::Key::World1        /* non-US #1 */
#define VE_KEY_WORLD_2         ::VoxelEngine::Key::World2        /* non-US #2 */
								 			 
/* Function keys */				 			 
#define VE_KEY_ESCAPE          ::VoxelEngine::Key::Escape
#define VE_KEY_ENTER           ::VoxelEngine::Key::Enter
#define VE_KEY_TAB             ::VoxelEngine::Key::Tab
#define VE_KEY_BACKSPACE       ::VoxelEngine::Key::Backspace
#define VE_KEY_INSERT          ::VoxelEngine::Key::Insert
#define VE_KEY_DELETE          ::VoxelEngine::Key::Delete
#define VE_KEY_RIGHT           ::VoxelEngine::Key::Right
#define VE_KEY_LEFT            ::VoxelEngine::Key::Left
#define VE_KEY_DOWN            ::VoxelEngine::Key::Down
#define VE_KEY_UP              ::VoxelEngine::Key::Up
#define VE_KEY_PAGE_UP         ::VoxelEngine::Key::PageUp
#define VE_KEY_PAGE_DOWN       ::VoxelEngine::Key::PageDown
#define VE_KEY_HOME            ::VoxelEngine::Key::Home
#define VE_KEY_END             ::VoxelEngine::Key::End
#define VE_KEY_CAPS_LOCK       ::VoxelEngine::Key::CapsLock
#define VE_KEY_SCROLL_LOCK     ::VoxelEngine::Key::ScrollLock
#define VE_KEY_NUM_LOCK        ::VoxelEngine::Key::NumLock
#define VE_KEY_PRINT_SCREEN    ::VoxelEngine::Key::PrintScreen
#define VE_KEY_PAUSE           ::VoxelEngine::Key::Pause
#define VE_KEY_F1              ::VoxelEngine::Key::F1
#define VE_KEY_F2              ::VoxelEngine::Key::F2
#define VE_KEY_F3              ::VoxelEngine::Key::F3
#define VE_KEY_F4              ::VoxelEngine::Key::F4
#define VE_KEY_F5              ::VoxelEngine::Key::F5
#define VE_KEY_F6              ::VoxelEngine::Key::F6
#define VE_KEY_F7              ::VoxelEngine::Key::F7
#define VE_KEY_F8              ::VoxelEngine::Key::F8
#define VE_KEY_F9              ::VoxelEngine::Key::F9
#define VE_KEY_F10             ::VoxelEngine::Key::F10
#define VE_KEY_F11             ::VoxelEngine::Key::F11
#define VE_KEY_F12             ::VoxelEngine::Key::F12
#define VE_KEY_F13             ::VoxelEngine::Key::F13
#define VE_KEY_F14             ::VoxelEngine::Key::F14
#define VE_KEY_F15             ::VoxelEngine::Key::F15
#define VE_KEY_F16             ::VoxelEngine::Key::F16
#define VE_KEY_F17             ::VoxelEngine::Key::F17
#define VE_KEY_F18             ::VoxelEngine::Key::F18
#define VE_KEY_F19             ::VoxelEngine::Key::F19
#define VE_KEY_F20             ::VoxelEngine::Key::F20
#define VE_KEY_F21             ::VoxelEngine::Key::F21
#define VE_KEY_F22             ::VoxelEngine::Key::F22
#define VE_KEY_F23             ::VoxelEngine::Key::F23
#define VE_KEY_F24             ::VoxelEngine::Key::F24
#define VE_KEY_F25             ::VoxelEngine::Key::F25
								 			 
/* Keypad */					 			 
#define VE_KEY_KP_0            ::VoxelEngine::Key::KP0
#define VE_KEY_KP_1            ::VoxelEngine::Key::KP1
#define VE_KEY_KP_2            ::VoxelEngine::Key::KP2
#define VE_KEY_KP_3            ::VoxelEngine::Key::KP3
#define VE_KEY_KP_4            ::VoxelEngine::Key::KP4
#define VE_KEY_KP_5            ::VoxelEngine::Key::KP5
#define VE_KEY_KP_6            ::VoxelEngine::Key::KP6
#define VE_KEY_KP_7            ::VoxelEngine::Key::KP7
#define VE_KEY_KP_8            ::VoxelEngine::Key::KP8
#define VE_KEY_KP_9            ::VoxelEngine::Key::KP9
#define VE_KEY_KP_DECIMAL      ::VoxelEngine::Key::KPDecimal
#define VE_KEY_KP_DIVIDE       ::VoxelEngine::Key::KPDivide
#define VE_KEY_KP_MULTIPLY     ::VoxelEngine::Key::KPMultiply
#define VE_KEY_KP_SUBTRACT     ::VoxelEngine::Key::KPSubtract
#define VE_KEY_KP_ADD          ::VoxelEngine::Key::KPAdd
#define VE_KEY_KP_ENTER        ::VoxelEngine::Key::KPEnter
#define VE_KEY_KP_EQUAL        ::VoxelEngine::Key::KPEqual
								 			 
#define VE_KEY_LEFT_SHIFT      ::VoxelEngine::Key::LeftShift
#define VE_KEY_LEFT_CONTROL    ::VoxelEngine::Key::LeftControl
#define VE_KEY_LEFT_ALT        ::VoxelEngine::Key::LeftAlt
#define VE_KEY_LEFT_SUPER      ::VoxelEngine::Key::LeftSuper
#define VE_KEY_RIGHT_SHIFT     ::VoxelEngine::Key::RightShift
#define VE_KEY_RIGHT_CONTROL   ::VoxelEngine::Key::RightControl
#define VE_KEY_RIGHT_ALT       ::VoxelEngine::Key::RightAlt
#define VE_KEY_RIGHT_SUPER     ::VoxelEngine::Key::RightSuper
#define VE_KEY_MENU            ::VoxelEngine::Key::Menu