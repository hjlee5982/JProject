#pragma once

#pragma warning(disable : 4244 4267 4819 4838 4996)

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define New DBG_NEW
#endif
#endif

#define DECLARE_SINGLETON(classname)		\
private:									\
	classname() { }							\
public:										\
	static classname* GetInstance()			\
	{										\
		static classname s_instance;		\
		return &s_instance;					\
	}

#define GET_SINGLETON(classname)	classname::GetInstance()

#define LOG		 GET_SINGLETON(Log)
#define JLOG	 GET_SINGLETON(JLog)
#define WINDOW	 GET_SINGLETON(Window)
#define DX		 GET_SINGLETON(DirectX11)
#define DEVICE	 GET_SINGLETON(DirectX11)->GetDevice()
#define CONTEXT  GET_SINGLETON(DirectX11)->GetContext()
#define GUI		 GET_SINGLETON(ImGuiManager)
#define INPUT	 GET_SINGLETON(InputManager)
#define TIME	 GET_SINGLETON(TimeManager)
#define SCENE    GET_SINGLETON(SceneManager)
#define FACTORY  GET_SINGLETON(ObjectFactory)
#define OBJECT   GET_SINGLETON(GameObjectManager)
#define ASSET    GET_SINGLETON(AssetManager)
//#define RENDERER GET_SINGLETON(Renderer)


//#define CHECK(p)	assert(SUCCEEDED(p))

#define ToDeg(value) XMConvertToDegrees(value)
#define ToRad(value) XMConvertToRadians(value)

#define JCLASS(classType)																	 \
bool registered_##classType =																 \
ObjectFactory::GetInstance()->RegisterObject												 \
(																							 \
	#classType, []()-> std::shared_ptr<GameObject> { return std::make_shared<classType>(); } \
)																							 \
