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
private:
	vector<sptr<class ImWindow>> _windows;
};

