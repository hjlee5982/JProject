#pragma once

class ImGuiManager
{
	DECLARE_SINGLETON(ImGuiManager)
public:
	void Init();
	void RenderBegin();
	void RenderEnd();
	void Shutdown();
private:
	void DockingSpace();
};

