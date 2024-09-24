#pragma once
#include <windows.h>
#include <memory>
#include "DirectXMath.h"
#include "SimpleMath.h"
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

using i8  = __int8;
using i16 = __int16;
using i32 = __int32;
using i64 = __int64;

using f32 = float;

using u8  = unsigned __int8;
using u16 = unsigned __int16;
using u32 = unsigned __int32;
using u64 = unsigned __int64;

using Color = DirectX::XMFLOAT4;

using vec2 = DirectX::SimpleMath::Vector2;
using vec3 = DirectX::SimpleMath::Vector3;
using vec4 = DirectX::SimpleMath::Vector4;
using matx = DirectX::SimpleMath::matx;
using quat = DirectX::SimpleMath::Quaternion;
using Ray  = DirectX::SimpleMath::Ray;

template<typename T>
using sptr = std::shared_ptr<T>;
template<typename T>
using uptr = std::unique_ptr<T>;
template<typename T>
using wptr = std::weak_ptr<T>;

template<class T>
using SortedSet = std::set<T>;
template<class T>
using HashSet = std::unordered_set<T>;
template<class Key, class Value>
using SortedMap = std::map<Key, Value>;
template<class Key, class Value>
using HashMap = std::unordered_map<Key, Value>;

template<typename T, class ...Args>
sptr<T> makeSptr(Args&& ... args)
{
	return std::make_shared<T>(std::forward<Args>(args)...);
}

template<typename T, class ...Args>
uptr<T> makeUptr(Args&& ... args)
{
	return std::make_unique<T>(std::forward<Args>(args)...);
}