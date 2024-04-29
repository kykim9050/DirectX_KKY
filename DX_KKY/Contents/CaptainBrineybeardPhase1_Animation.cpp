#include "PreCompile.h"

#include "CaptainBrineybeardPhase1.h"

void ACaptainBrineybeardPhase1::CreateAnimation()
{
	// Ship
	ShipRailRenderer->CreateAnimation(PirateBossAniName::Ship_Rail, "Ship_Rail", 0.065f);
	ShipMastRenderer->SetSprite("Ship_Mast.png");
	ShipSailRenderer->CreateAnimation(PirateBossAniName::Ship_Sail, "Ship_Sail", 0.05f);
	
	ShipRenderer->CreateAnimation(PirateBossAniName::Ship_Phase1_Idle, "Ship_Phase1_Idle", 0.065f);
	ShipRenderer->CreateAnimation(PirateBossAniName::Ship_Phase1_Blink, "Ship_Phase1_Blink", 0.065f);

	// Pirate
	PirateRenderer->CreateAnimation(PirateBossAniName::Pirate_Intro, "Pirate_Intro", 0.047f, true, 0, 4);
	PirateRenderer->CreateAnimation(PirateBossAniName::Pirate_Laugh, "Pirate_Intro",
		{ 0.047f,  0.047f , 0.047f , 0.047f , 0.047f , 0.047f , 0.047f , 0.047f , 0.047f , 0.047f , 0.047f , 0.047f},
		{ 4, 5, 6, 7, 8, 9, 10, 9, 8, 7, 6, 5 }, true);
	PirateRenderer->CreateAnimation(PirateBossAniName::Pirate_StopLaugh, "Pirate_Intro", { 0.047f ,0.047f ,0.047f }, { 11, 12, 13 }, false);
	PirateRenderer->CreateAnimation(PirateBossAniName::Pirate_Idle, "Pirate_Idle", 0.047f);

	// Animation Change
	ShipRailRenderer->ChangeAnimation(PirateBossAniName::Ship_Rail);
	ShipSailRenderer->ChangeAnimation(PirateBossAniName::Ship_Sail);
}

void ACaptainBrineybeardPhase1::SetAnimationCallback()
{
	// ship
	{
		ShipRenderer->SetLastFrameCallback(PirateBossAniName::Ship_Phase1_Blink, [this]()
			{
				ShipRenderer->ChangeAnimation(PirateBossAniName::Ship_Phase1_Idle);
			});
	}


	// Pirate
	{
		PirateRenderer->SetLastFrameCallback(PirateBossAniName::Pirate_StopLaugh, [this]()
			{
				PirateState.ChangeState("Pirate_Idle");
			});
	}
}