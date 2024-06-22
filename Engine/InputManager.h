#pragma once

//enum class KEY_TYPE
//{
//	UP    = VK_UP,
//	DOWN  = VK_DOWN,
//	LEFT  = VK_LEFT,
//	RIGHT = VK_RIGHT,
//
//	W = 'W',
//	A = 'A',
//	S = 'S',
//	D = 'D',
//
//	KEY_1 = '1',
//	KEY_2 = '2',
//	KEY_3 = '3',
//	KEY_4 = '4',
//
//	LBUTTON = VK_LBUTTON,
//	RBUTTON = VK_RBUTTON,
//};
//
//enum class KEY_STATE
//{
//	NONE,
//	PRESS,
//	DOWN,
//	UP,
//	END
//};
//
//enum class MOUSE_STATE
//{
//	X,
//	Y,
//	WHEEL,
//	END
//};
//
//enum
//{
//	KEY_TYPE_COUNT    = static_cast<i32>(UINT8_MAX + 1),
//	KEY_STATE_COUNT   = static_cast<i32>(KEY_STATE::END),
//	MOUSE_STATE_COUNT = static_cast<i32>(MOUSE_STATE::END),
//};
//
//class InputManager
//{
//	DECLARE_SINGLETON(InputManager);
//public:
//	void Init(HWND hWnd, HINSTANCE hInst);
//	void Update();
//public:
//	bool GetButtonUp(KEY_TYPE key)
//	{
//		return GetState(key) == KEY_STATE::UP; 
//	}
//	bool GetButtonDown(KEY_TYPE key) 
//	{
//		return GetState(key) == KEY_STATE::DOWN;
//	}
//	bool GetButtonPress(KEY_TYPE key) 
//	{
//		return GetState(key) == KEY_STATE::PRESS; 
//	}
//public:
//	const POINT& GetMousePos() 
//	{
//		return mMousePos; 
//	}
//private:
//	inline KEY_STATE GetState(KEY_TYPE key)
//	{
//		return mStates[static_cast<u8>(key)]; 
//	}
//private:
//	vector<KEY_STATE> mStates;
//private:
//	POINT mMousePos = {};
//	HWND  mhWnd;
//public:
//	i32 MouseMove(MOUSE_STATE mouseState)
//	{
//		return ((i32*)&mMouseState)[(i32)mouseState];
//	}
//private:
//	IDirectInput8*       mInputSDK = nullptr;
//	IDirectInputDevice8* mMouse    = nullptr;
//	DIMOUSESTATE mMouseState;
//};

#define KEY_W 0x00000001
#define KEY_A 0x00000002
#define KEY_S 0x00000004
#define KEY_D 0x00000008

#define KEY_Q 0x00000010
#define KEY_E 0x00000020
#define KEY_Z 0x00000040
#define KEY_C 0x00000080

#define LBTN  0x00000100
#define RBTN  0x00000200

enum class MOUSE_STATE
{
	X,
	Y,
	WHEEL,

	END
};

class InputManager
{
	DECLARE_SINGLETON(InputManager)
public:
	void Init(HWND hWnd, HINSTANCE hInst);
	void Update();
public:
	bool KeyUp(DWORD key);
	bool KeyDown(DWORD key);
	bool KeyPress(DWORD key);
public:
	i32 MouseMove(MOUSE_STATE state)
	{
		return ((i32*)&_mouseState)[(u32)state];
	}
private:
	HWND _hWnd;
private:
	DWORD _key     = 0;
	DWORD _keyDown = 0;
	DWORD _keyUp   = 0;
private:
	IDirectInput8*       _inputSDK = nullptr;
	IDirectInputDevice8* _mouse    = nullptr;
private:
	DIMOUSESTATE _mouseState;
};