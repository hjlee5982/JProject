#include "pch.h"
#include "ImConsole.h"

void ImConsole::Init()
{
}

void ImConsole::Update()
{
	ImGui::Begin("Console");
	IMFOCUS("Console");

	JLOG->Draw();

	ImGui::End();
}
