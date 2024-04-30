#include "PreCompile.h"

#include "CaptainBrineybeardPhase2.h"

void ACaptainBrineybeardPhase2::CreateAnimation()
{
	ShipRenderer->CreateAnimation(PirateBossAniName::Ship_Phase2_Transform_Idle, "Ship_Transform", 0.065f, true, 9, 10);
}

void ACaptainBrineybeardPhase2::SetAnimationCallback()
{

}