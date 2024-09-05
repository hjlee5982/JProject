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
	vector<sptr<class ImWindow>> _windows;
public:
	void Notify(sptr<GameObject> go);
private:
	sptr<GameObject> _go;
};

