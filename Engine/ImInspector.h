#pragma once

#include "ImWindow.h"

class ImInspector : public ImWindow
{
public:
	virtual ~ImInspector() = default;
public:
	virtual void Init()   override;
	virtual void Update() override;
private:
	void RenderTransformInspector();
	void RenderCameraInspector();
	void RenderMeshRendererInspector();
	void RenderScriptInspector();
public:
	virtual void StateUpdate(sptr<GameObject> go) override;
private:
	sptr<GameObject> _go;
};

