#include "PreCompile.h"

#include "FlowerLevelDebugWindow.h"

UFlowerLevelDebugWindow::UFlowerLevelDebugWindow()
{
}

UFlowerLevelDebugWindow::~UFlowerLevelDebugWindow()
{
}

void UFlowerLevelDebugWindow::Init()
{
	Super::Init();


}

void UFlowerLevelDebugWindow::Tick(ULevel* Level, float _Delta)
{
	Super::Tick(Level, _Delta);
}

void UFlowerLevelDebugWindow::OnGui(ULevel* Level, float _Delta)
{
	if (false == IsPhase2)
	{
		if (true == ImGui::Button("CreateObject"))
		{
			PhaseSetFunction(static_cast<int>(EFlowerBossPattern::CreateObject));
		}

		if (true == ImGui::Button("Gatling"))
		{
			PhaseSetFunction(static_cast<int>(EFlowerBossPattern::Gatling));
		}

		if (true == ImGui::Button("FaceAttack_High"))
		{
			PhaseSetFunction(static_cast<int>(EFlowerBossPattern::FaceAttack_High));
		}

		if (true == ImGui::Button("FaceAttack_Low"))
		{
			PhaseSetFunction(static_cast<int>(EFlowerBossPattern::FaceAttack_Low));
		}

		if (true == ImGui::Button("Phase2"))
		{
			IsPhase2 = true;
			PhaseSetFunction(static_cast<int>(EFlowerBossPattern::Phase2));
		}
	}
}