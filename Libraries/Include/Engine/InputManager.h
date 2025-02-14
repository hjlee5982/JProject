#pragma once

enum KeyCode
{
	// 마우스
	L_BUTTON = 0x01,
	R_BUTTON = 0x02,
	M_BUTTON = 0x04,

	PRINT_SCREEN = 0x2C,
	SCROLL_LOCK  = 0x91,
	PAUSE        = 0x13,

	INSERT    =	0x2D,
	DEL	      = 0x2E,
	HOME	  = 0x24,
	END		  = 0x23,
	PAGE_UP   =	0x21,
	PAGE_DOWN =	0x22,

	UP    =	0x26,	
	DOWN  =	0x28,
	LEFT  =	0x25,
	RIGHT =	0x27,

	ESC      = 0x1B,
	TAB      = 0x09,
	CAPSLOCK = 0x14,


	ENTER = 0x0D,
	SPACE =	0x20,

	// 키보드 위 숫자 키
	ALPHA_0 = 0x30,
	ALPHA_1 = 0x31,
	ALPHA_2 = 0x32,
	ALPHA_3 = 0x33,
	ALPHA_4 = 0x34,
	ALPHA_5 = 0x35,
	ALPHA_6 = 0x36,
	ALPHA_7 = 0x37,
	ALPHA_8 = 0x38,
	ALPHA_9 = 0x39,

	A = 0x41,
	B = 0x42,
	C = 0x43,
	D = 0x44,
	E = 0x45,
	F = 0x46,
	G = 0x47,
	H = 0x48,
	I = 0x49,
	J = 0x4A,
	K = 0x4B,
	L = 0x4C,
	M = 0x4D,
	N = 0x4E,
	O = 0x4F,
	P = 0x50,
	Q = 0x51,
	R = 0x52,
	S = 0x53,
	T = 0x54,
	U = 0x55,
	V = 0x56,
	W = 0x57,
	X = 0x58,
	Y = 0x59,
	Z = 0x5A,

	// 키패드
	KEYPAD_0 = 0x60,
	KEYPAD_1 = 0x61,
	KEYPAD_2 = 0x62,
	KEYPAD_3 = 0x63,
	KEYPAD_4 = 0x64,
	KEYPAD_5 = 0x65,
	KEYPAD_6 = 0x66,
	KEYPAD_7 = 0x67,
	KEYPAD_8 = 0x68,
	KEYPAD_9 = 0x69,

	F1	= 0x70,
	F2	= 0x71,
	F3	= 0x72,
	F4	= 0x73,
	F5	= 0x74,
	F6	= 0x75,
	F7	= 0x76,
	F8	= 0x77,
	F9	= 0x78,
	F10	= 0x79,
	F11	= 0x7A,
	F12	= 0x7B,

	L_SHIFT		= 0xA0,
	R_SHIFT		= 0xA1,
	L_CONTROL	= 0xA2,
	R_CONTROL	= 0xA3,
	L_ALT		= 0xA4,
	R_ALT		= 0xA5,
};

class InputManager
{
	SINGLETON(InputManager)
public:
	void Init();
	void Update();
public:
	bool GetKey    (KeyCode key); // 눌려있는지
	bool GetKeyUp  (KeyCode key); // 눌렀는지
	bool GetKeyDown(KeyCode key); // 뗐는지
public:
	bool GetMouseButton    (KeyCode key);
	bool GetMouseButtonUp  (KeyCode key);
	bool GetMouseButtonDown(KeyCode key);
public:
	int GetMouseDeltaX() const
	{
		return _mouseDeltaX;
	}
	int GetMouseDeltaY() const
	{
		return _mouseDeltaY;
	}
private:
	HashMap<int, bool> _prevKey; // 이전 프레임 키
	HashMap<int, bool> _currKey; // 현재 프레임 키
private:
	HashMap<int, bool> _prevMouse; // 이전 프레임 마우스 
	HashMap<int, bool> _currMouse; // 현재 프레임 마우스
private:
	POINT _prevMousePos = { 0, 0 };
	POINT _currMousePos = { 0, 0 };
	int   _mouseDeltaX  = 0;
	int   _mouseDeltaY  = 0;
};