#include "PreCompile.h"

#include "PirateLevelDebugWindow.h"

UPirateLevelDebugWindow::UPirateLevelDebugWindow()
{
}

UPirateLevelDebugWindow::~UPirateLevelDebugWindow()
{
}

void UPirateLevelDebugWindow::Init()
{
	Super::Init();
}

void UPirateLevelDebugWindow::Tick(ULevel* Level, float _Delta)
{
	Super::Tick(Level, _Delta);
}

void UPirateLevelDebugWindow::OnGui(ULevel* Level, float _Delta)
{
	if (true == ImGui::Button("SharkAppear"))
	{
		int a = 0;
		return;
	}
}
