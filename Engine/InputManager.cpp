#include "pch.h"
#include "InputManager.h"

void InputManager::Init()
{
}

void InputManager::Update()
{
    _prevKey      = _currKey;
    _prevMouse    = _currMouse;
    _prevMousePos = _currMousePos;

    for (int key = 0; key < 256; key++)
    {
        _currKey[key] = (GetAsyncKeyState(key) & 0x8000) != 0;
    }

    _currMouse[1] = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0;
    _currMouse[2] = (GetAsyncKeyState(VK_RBUTTON) & 0x8000) != 0;
    _currMouse[4] = (GetAsyncKeyState(VK_MBUTTON) & 0x8000) != 0;

    GetCursorPos(&_currMousePos);

    _mouseDeltaX = _currMousePos.x - _prevMousePos.x;
    _mouseDeltaY = _currMousePos.y - _prevMousePos.y;
}

bool InputManager::GetKey(KeyCode key)
{
    return _currKey[int(key)];
}

bool InputManager::GetKeyUp(KeyCode key)
{
    return _currKey[int(key)] && _prevKey[int(key)];
}

bool InputManager::GetKeyDown(KeyCode key)
{
    return _currKey[int(key)] && !_prevKey[int(key)];
}

bool InputManager::GetMouseButton(KeyCode key)
{
    return _currMouse[int(key)];
}

bool InputManager::GetMouseButtonUp(KeyCode key)
{
    return _currMouse[int(key)] && _prevMouse[int(key)];
}

bool InputManager::GetMouseButtonDown(KeyCode key)
{
    return _currMouse[int(key)] && !_prevMouse[int(key)];
}
