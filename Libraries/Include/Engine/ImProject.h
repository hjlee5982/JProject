#pragma once

#include "ImWindow.h"

class ImProject : public ImWindow
{
public:
	virtual ~ImProject() = default;
public:
	virtual void Init()   override;
	virtual void Update() override;
private:
	void RenderFileExplorer(const std::filesystem::path& path);
	void RenderFolderItems();
private:
	string _selectedPath = "..\\Assets";
private:
	ImGuiTreeNodeFlags nodeFlag = ImGuiTreeNodeFlags_OpenOnDoubleClick;
public:
	virtual void StateUpdate(sptr<GameObject> go) override {}
};
