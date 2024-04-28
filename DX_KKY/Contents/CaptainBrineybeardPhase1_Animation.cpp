#include "PreCompile.h"

#include "CaptainBrineybeardPhase1.h"

void ACaptainBrineybeardPhase1::CreateAnimation()
{
	// Ship
	ShipRenderer->CreateAnimation(PirateBossAniName::Ship_Phase1_Idle, "Ship_Phase1_Idle", 0.065f);

	{
		ShipRenderer->ChangeAnimation(PirateBossAniName::Ship_Phase1_Idle);
	}
}