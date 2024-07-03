#pragma once

#include "Layer.h"

class GameObjectManager
{
	DECLARE_SINGLETON(GameObjectManager);
public:
	void Init();
	void Update();
	void LateUpdate();
	void Render();
public:
	void AddGameObject(sptr<GameObject> go);
private:
	HashMap<GameObject::ELayerType, sptr<Layer>> _layers;

	/////// Deferred Test
private:
	ComPtr<ID3D11RenderTargetView> _originRenderTargetView = nullptr;
	ComPtr<ID3D11DepthStencilView> _originDepthStencilView = nullptr;
};

