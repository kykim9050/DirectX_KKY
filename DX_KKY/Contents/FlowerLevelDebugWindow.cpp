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
			Function();
		}

		if (true == ImGui::Button("Gatling"))
		{

		}

		if (true == ImGui::Button("FaceAttack_High"))
		{

		}

		if (true == ImGui::Button("FaceAttack_Low"))
		{

		}
	}

	if (true == ImGui::Button("Phase2"))
	{
		IsPhase2 = true;

	}

}