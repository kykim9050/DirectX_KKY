#include "PreCompile.h"

#include "CaptainBrineybeardPhase2.h"

void ACaptainBrineybeardPhase2::CreateAnimation()
{
	ShipRenderer->CreateAnimation(PirateBossAniName::Ship_Phase2_Transform_Idle, "Ship_Transform", 0.047f, true, 9, 10);
	ShipRenderer->CreateAnimation(PirateBossAniName::Ship_Phase2_Transform_End, "Ship_Transform", 0.047f, false, 11, 17);
	ShipRenderer->CreateAnimation(PirateBossAniName::Ship_Phase2_Idle, "Ship_Phase2_Idle", 0.047f);
}

void ACaptainBrineybeardPhase2::SetAnimationCallback()
{
	ShipRenderer->SetLastFrameCallback(PirateBossAniName::Ship_Phase2_Transform_End, [this]()
		{
			ShipState.ChangeState(PirateBossState::Ship_Phase2_Idle);
		});
}