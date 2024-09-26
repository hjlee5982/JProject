#include "pch.h"
#include "ImConsole.h"

void ImConsole::Init()
{
}

void ImConsole::Update()
{
	IMFOCUS("Console");
	ImGui::Begin("Console");
	{
		JLOG->Draw();
	}
	ImGui::End();
}
