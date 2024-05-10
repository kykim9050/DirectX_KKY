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
		if (nullptr != SharkAppearFunction)
		{
			SharkAppearFunction();
		}
	}

	if (true == ImGui::Button("SeaDogAppear"))
	{
		if (nullptr != SeaDogAppearFunction)
		{
			SeaDogAppearFunction();
		}
	}

	if (false == IsPhase2)
	{
		if (true == ImGui::Button("ShootCannonBall"))
		{
			OtherSetFunction(static_cast<int>(EPirateBossPattern::ShootCanonBall));
		}

		if (true == ImGui::Button("OctopusShootAtt"))
		{
			OtherSetFunction(static_cast<int>(EPirateBossPattern::OctopusShootAtt));
		}

		if (true == ImGui::Button("Phase2"))
		{
			IsPhase2 = true;
			OtherSetFunction(static_cast<int>(EPirateBossPattern::Phase2));
		}
	}
}