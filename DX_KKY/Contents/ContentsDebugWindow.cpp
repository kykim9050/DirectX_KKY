#include "PreCompile.h"

#include "ContentsDebugWindow.h"

UContentsDebugWindow::UContentsDebugWindow()
{
}

UContentsDebugWindow::~UContentsDebugWindow()
{
}

void UContentsDebugWindow::Init()
{
	Super::Init();
}

void UContentsDebugWindow::Tick(ULevel* Level, float _Delta)
{
	Super::Tick(Level, _Delta);
}

void UContentsDebugWindow::OnGui(ULevel* Level, float _Delta)
{
	ImGui::Button("TitleLevel", ImVec2(20, 20));
}
