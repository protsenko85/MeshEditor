#pragma once
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <functional>
#include <iostream>
enum class Modifier
{
	NoModifier = 0,
	Shift = 1,
	Control = 2,
	Alt = 4,
	Super = 8,
};
enum class Action
{
	Release = 0,
	Press = 1,
	Repeat = 2,
};
enum class ButtonCode
{
	Button_0 = 0,
	Button_1 = 1,
	Button_2 = 2,
	Button_3 = 3,
	Button_4 = 4,
	Button_5 = 5,
	Button_6 = 6,
	Button_7 = 7
};
enum class KeyCode
{
	UNKNOWN = -1,
	Space = 32,
	Apostrophe = 39,
	Comma = 44,
	Minus = 45,
	Period = 46,
	Slash = 47,
	Key_0 = 48,
	Key_1 = 49,
	Key_2 = 50,
	Key_3 = 51,
	Key_4 = 52,
	Key_5 = 53,
	Key_6 = 54,
	Key_7 = 55,
	Key_8 = 56,
	Key_9 = 57,
	Semicolon = 59,
	Equal = 61,
	Key_A = 65,
	Key_B = 66,
	Key_C = 67,
	Key_D = 68,
	Key_E = 69,
	Key_F = 70,
	Key_G = 71,
	Key_H = 72,
	Key_I = 73,
	Key_J = 74,
	Key_K = 75,
	Key_L = 76,
	Key_M = 77,
	Key_N = 78,
	Key_O = 79,
	Key_P = 80,
	Key_Q = 81,
	Key_R = 82,
	Key_S = 83,
	Key_T = 84,
	Key_U = 85,
	Key_V = 86,
	Key_W = 87,
	Key_X = 88,
	Key_Y = 89,
	Key_Z = 90,
	LeftBracket = 91,
	BackSlash = 92,
	RightBracket = 93,
	GraveAccent = 96,
	World_1 = 161,
	World_2 = 162,
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
	Key_F1 = 290,
	Key_F2 = 291,
	Key_F3 = 292,
	Key_F4 = 293,
	Key_F5 = 294,
	Key_F6 = 295,
	Key_F7 = 296,
	Key_F8 = 297,
	Key_F9 = 298,
	Key_F10 = 299,
	Key_F11 = 300,
	Key_F12 = 301,
	Key_F13 = 302,
	Key_F14 = 303,
	Key_F15 = 304,
	Key_F16 = 305,
	Key_F17 = 306,
	Key_F18 = 307,
	Key_F19 = 308,
	Key_F20 = 309,
	Key_F21 = 310,
	Key_F22 = 311,
	Key_F23 = 312,
	Key_F24 = 313,
	Key_F25 = 314,
	Key_KP_0 = 320,
	Key_KP_1 = 321,
	Key_KP_2 = 322,
	Key_KP_3 = 323,
	Key_KP_4 = 324,
	Key_KP_5 = 325,
	Key_KP_6 = 326,
	Key_KP_7 = 327,
	Key_KP_8 = 328,
	Key_KP_9 = 329,
	KP_Decimal = 330,
	KP_Divide = 331,
	KP_Multiply = 332,
	KP_Subtract = 333,
	KP_Add = 334,
	KP_Enter = 335,
	KP_Equal = 336,
	LeftShift = 340,
	LeftControl = 341,
	LeftAlt = 342,
	LeftSuper = 343,
	RightShift = 344,
	RightControl = 345,
	RightAlt = 346,
	RightSuper = 347,
	Menu = 348,
};

class GLWindow
{
public:
	using KeyCallback = std::function<void(KeyCode, Action, Modifier)>;
	using CursorPosCallback = std::function<void(double, double)>;
	using MouseCallback = std::function<void(ButtonCode, Action, Modifier)>;
	using ScrollCallback = std::function<void(double, double)>;
	GLWindow(const std::string& title, uint32_t width, uint32_t height);
	~GLWindow();
	uint32_t getWidth() const;
	uint32_t getHeight() const;
	KeyCallback getKeyCallback() const;
	MouseCallback getMouseCallback() const;
	CursorPosCallback getCursorCallback() const;
	ScrollCallback getScrollCallback() const;
	void setKeyCallback(const KeyCallback& callback);
	void setCursorPosCallback(const CursorPosCallback& callback);
	void setMouseCallback(const MouseCallback& callback);
	void setScrollCallback(const ScrollCallback& callback);
	GLFWwindow* getGLFWHandle() const;
private:
	GLFWwindow* handle;
	ScrollCallback scrollCallback;
	KeyCallback keyCallBack;
	CursorPosCallback cursorCallback;
	MouseCallback mouseCallback;
	uint32_t width, height;
};