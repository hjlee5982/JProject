#include "pch.h"
#include "InputManager.h"

//void InputManager::Init(HWND hWnd, HINSTANCE hInst)
//{
//	mhWnd = hWnd;
//	mStates.resize(KEY_TYPE_COUNT, KEY_STATE::NONE);
//
//	HRESULT hr;
//
//	hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&mInputSDK, nullptr);
//	CHECK(hr);
//
//	hr = mInputSDK->CreateDevice(GUID_SysMouse, &mMouse, nullptr);
//	CHECK(hr);
//
//	hr = mMouse->SetDataFormat(&c_dfDIMouse);
//	CHECK(hr);
//
//	hr = mMouse->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);
//	CHECK(hr);
//
//	hr = mMouse->Acquire();
//	CHECK(hr);
//}
//
//void InputManager::Update()
//{
//	HWND hwnd = ::GetActiveWindow();
//
//	if (mhWnd != hwnd)
//	{
//		for (u32 key = 0; key < KEY_TYPE_COUNT; key++)
//		{
//			mStates[key] = KEY_STATE::NONE;
//		}
//
//		return;
//	}
//
//	BYTE asciiKeys[KEY_TYPE_COUNT] = {};
//
//	if (::GetKeyboardState(asciiKeys) == false)
//	{
//		return;
//	}
//
//	for (u32 key = 0; key < KEY_TYPE_COUNT; key++)
//	{
//		// 키가 눌려 있으면 true
//		if (asciiKeys[key] & 0x80)
//		{
//			KEY_STATE& state = mStates[key];
//
//			// 이전 프레임에 키를 누른 상태라면 PRESS
//			if (state == KEY_STATE::PRESS || state == KEY_STATE::DOWN)
//			{
//				state = KEY_STATE::PRESS;
//			}
//			else
//			{
//				state = KEY_STATE::DOWN;
//			}
//		}
//		else
//		{
//			KEY_STATE& state = mStates[key];
//
//			// 이전 프레임에 키를 누른 상태라면 UP
//			if (state == KEY_STATE::PRESS || state == KEY_STATE::DOWN)
//			{
//				state = KEY_STATE::UP;
//			}
//			else
//			{
//				state = KEY_STATE::NONE;
//			}
//		}
//	}
//
//	mMouse->GetDeviceState(sizeof(mMouseState), &mMouseState);
//
//	::GetCursorPos(&mMousePos);
//	::ScreenToClient(mhWnd, &mMousePos);
//}

void InputManager::Init(HWND hWnd, HINSTANCE hInst)
{
	_hWnd = hWnd;

	HRESULT hr;

	hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&_inputSDK, nullptr);
	CHECK(hr);

	hr = _inputSDK->CreateDevice(GUID_SysMouse, &_mouse, nullptr);
	CHECK(hr);

	hr = _mouse->SetDataFormat(&c_dfDIMouse);
	CHECK(hr);

	hr = _mouse->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);
	CHECK(hr);

	hr = _mouse->Acquire();
	CHECK(hr);

	JLOG_INIT("Input Init Complete");
}

void InputManager::Update()
{
	_key = 0;

	if (GetAsyncKeyState('W') & 0x8000) { _key |= KEY_W; }
	if (GetAsyncKeyState('A') & 0x8000) { _key |= KEY_A; }
	if (GetAsyncKeyState('S') & 0x8000) { _key |= KEY_S; }
	if (GetAsyncKeyState('D') & 0x8000) { _key |= KEY_D; }
	if (GetAsyncKeyState('Q') & 0x8000) { _key |= KEY_Q; }
	if (GetAsyncKeyState('E') & 0x8000) { _key |= KEY_E; }
	if (GetAsyncKeyState('Z') & 0x8000) { _key |= KEY_Z; }
	if (GetAsyncKeyState('C') & 0x8000) { _key |= KEY_C; }

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) { _key |= LBTN; }
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000) { _key |= RBTN; }

	_mouse->GetDeviceState(sizeof(_mouseState), &_mouseState);
}

bool InputManager::KeyUp(DWORD key)
{
	if (_key & key)
	{
		_keyUp |= key;
		return false;
	}
	else if (_keyUp & key)
	{
		_keyUp ^= key;
		return false;
	}

	return false;
}

bool InputManager::KeyDown(DWORD key)
{
	if (_key & key && !(_keyDown & key))
	{
		_keyDown |= key;
		return true;
	}
	else if (!(_key & key) && (_keyDown & key))
	{
		_keyDown ^= key;
		return false;
	}

	return false;
}

bool InputManager::KeyPress(DWORD key)
{
	if (_key & key)
	{
		return true;
	}

	return false;
}
