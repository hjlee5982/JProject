#pragma once

#define IMFOCUS(name)																		  \
																							  \
if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))											  \
{																							  \
	ImVec2 mouse_pos   = ImGui::GetMousePos();												  \
	ImVec2 window_pos  = ImGui::GetWindowPos();												  \
	ImVec2 window_size = ImGui::GetWindowSize();											  \
																							  \
	if (mouse_pos.x >= window_pos.x && mouse_pos.x <= window_pos.x + window_size.x &&		  \
		mouse_pos.y >= window_pos.y && mouse_pos.y <= window_pos.y + window_size.y)			  \
	{																						  \
		ImGui::SetWindowFocus();															  \
	}																						  \
}																							  \
																							  \
if (ImGui::IsWindowFocused())		 														  \
{									 														  \
	GUI->NotifyWindow(name);      	     													  \
}

class ImGuiManager
{
	DECLARE_SINGLETON(ImGuiManager)
public:
	void Init();
	void RenderBegin();
	void Update();
	void RenderEnd();
	void Shutdown();
public:
	void Image(const wstring& name, ImVec2 size = ImVec2(16, 16));
public:
	void AddWindows(sptr<class ImWindow> window, string name);
public:
	void SetFocusedWindow(const string& name)
	{
		_focusedWindow = name;
	}
	const string& GetFocusedWindow()
	{
		return _focusedWindow;
	}
public:
	void GUI_Thread();
	void Destroy()
	{
		_destroy = false;
	}
private:
	vector<sptr<class ImWindow>> _windows;
public:
	// 각 윈도우에게 어떤 오브젝트가 선택되었는지 알려줌
	void Notify(sptr<GameObject> go);
	// 어떤 윈도우가 포커싱이 되어있는지 유저에게 알려줌 
	void NotifyWindow(const string& name);
private:
	sptr<GameObject> _go;
	string _focusedWindow;
public:
	ImFont* _koreanFont;
private:
	std::mutex _mutex;
	bool _destroy = true;
};

