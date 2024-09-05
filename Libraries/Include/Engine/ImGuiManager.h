#pragma once

class ImGuiManager
{
	DECLARE_SINGLETON(ImGuiManager)
public:
	void Init();
	void RenderBegin();
	void Update();
	void RenderEnd();
	void Shutdown();
private:
	void DockingSpace();
public:
	void SetState(sptr<GameObject> go);
public:
	void Notify();
private:
	vector<sptr<class ImWindow>> _windows;
private:
	sptr<GameObject> _go;
};

