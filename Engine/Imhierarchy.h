#pragma once

#include "ImWindow.h"

class Imhierarchy : public ImWindow
{
public:
	virtual ~Imhierarchy() = default;
public:
	virtual void Init()   override;
	virtual void Update() override;
public:
	virtual void StateUpdate(sptr<GameObject> go) override {}
private:
	ComPtr<ID3D11ShaderResourceView> _icon;
private:
	HashMap<string, bool> _selected;
	bool _on = true;
};

