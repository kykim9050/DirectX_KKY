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
	if (true == ImGui::Button("TitleLevel"))
	{
		GEngine->ChangeLevel("TitleLevel");
		return;
	}

	if (true == ImGui::Button("EndingLevel"))
	{
		GEngine->ChangeLevel("EndingLevel");
	}

	//if (true == ImGui::Button("TutorialLevel"))
	//{
	//	GEngine->ChangeLevel("TutorialLevel");
	//}

	if (true == ImGui::Button("WorldLevel"))
	{
		GEngine->ChangeLevel("WorldLevel");
	}

	//if (true == ImGui::Button("TestLevel"))
	//{
	//	GEngine->ChangeLevel("TestLevel");
	//}

	if (true == ImGui::Button("FlowerLevel"))
	{
		GEngine->ChangeLevel("FlowerLevel");
	}

}
