#pragma once

// Headers **********************************************
#include "Types.h"
#include "Define.h"


// FileSystem *******************************************
#include <filesystem>


// STL **************************************************
#include <string>
#include <memory>
#include <iostream>
#include <array>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <functional>
using namespace std;
#include <any>


// Multithread ******************************************
#include <thread>
#include <atomic>
#include <mutex>


// Win **************************************************
#include <windows.h>
#include <assert.h>
#include <optional>
#include <comdef.h>


// DirecX ***********************************************
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#include <d3d11.h>
#include <d3dcompiler.h>
#include <d3d11shader.h>
#include <d3d11.h>
#include <wrl.h>
#include <DirectXMath.h>
#include <DirectXTex/DirectXTex.h>
#include <DirectXTex/DirectXTex.inl>
#include <FX11/d3dx11effect.h>
#include <DirectXColors.h>
using namespace DirectX;
using namespace Microsoft::WRL;


// ImGui ************************************************
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"


// RapidJson ********************************************
#define RAPIDSON_HAS_STDSTRING 1

//#include "rapidjson/document.h"
//#include "rapidjson/writer.h"
//#include "rapidjson/prettywriter.h"
//#include "rapidjson/stringbuffer.h"
//#include "rapidjson/filereadstream.h"
//#include "rapidjson/filewritestream.h"
//using namespace rapidjson;
#include "JsonData.h"


// Libs *************************************************
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#ifdef _DEBUG
#pragma comment(lib, "DirectXTex/DirectXTex_debug.lib")
#pragma comment(lib, "FX11/Effects11d.lib")
#else
#pragma comment(lib, "DirectXTex/DirectXTex.lib")
#pragma comment(lib, "FX11/Effects11.lib")
#endif


// Utils *************************************************
#include "Log.h"
#include "JLog.h"
#include "Exception.h"
#include "Utils.h"
#include "Enum.h"


// Engine ************************************************
#include "Window.h"
#include "Device.h"
//#include "Renderer.h"
#include "VertexData.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "Shader.h"
#include "ShaderDesc.h"
#include "GameObject.h"


// Asset **********************************************************
#include "Mesh.h"
#include "Texture.h"
#include "Material.h"
#include "Script.h"


// Component **********************************************************
#include "Transform.h"
#include "Camera.h"
#include "Light.h"
#include "MeshRenderer.h"
#include "PickingCollider.h"
#include "BoxCollider.h"
#include "SphereCollider.h"


// Singleton **********************************************************
#include "ImGuiManager.h"
#include "InputManager_Legacy.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "AssetManager.h"
#include "GameObjectManager.h"
#include "ObjectFactory.h"