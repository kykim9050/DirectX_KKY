#include "PreCompile.h"

#include "CaptainBrineybeardPhase1.h"

void ACaptainBrineybeardPhase1::CreateAnimation()
{
	// Ship
	ShipRenderer->CreateAnimation(PirateBossAniName::Ship_Phase1_Idle, "Ship_Phase1_Idle", 0.065f);
	ShipRailRenderer->CreateAnimation(PirateBossAniName::Ship_Rail, "Ship_Rail", 0.065f);
	ShipMastRenderer->SetSprite("Ship_Mast.png");
	ShipSailRenderer->CreateAnimation(PirateBossAniName::Ship_Sail, "Ship_Sail", 0.065f);

	ShipRenderer->ChangeAnimation(PirateBossAniName::Ship_Phase1_Idle);
	ShipRailRenderer->ChangeAnimation(PirateBossAniName::Ship_Rail);
	ShipSailRenderer->ChangeAnimation(PirateBossAniName::Ship_Sail);
}