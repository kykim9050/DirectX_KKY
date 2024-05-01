#include "PreCompile.h"

#include "CaptainBrineybeardPhase2.h"

void ACaptainBrineybeardPhase2::CreateAnimation()
{
	// ship
	ShipRenderer->CreateAnimation(PirateBossAniName::Ship_Phase2_Transform_Idle, "Ship_Transform", 0.047f, true, 9, 10);
	ShipRenderer->CreateAnimation(PirateBossAniName::Ship_Phase2_Transform_End, "Ship_Transform", 0.047f, false, 11, 17);
	ShipRenderer->CreateAnimation(PirateBossAniName::Ship_Phase2_Idle, "Ship_Phase2_Idle", 0.047f);
	ShipRenderer->CreateAnimation(PirateBossAniName::Ship_Phase2_LazarAtt_Begin, "Ship_phase2_Lazar_Begin", 0.047f, false, 0, 5);
	ShipRenderer->CreateAnimation(PirateBossAniName::Ship_Phase2_LazarAtt_Charging, "Ship_phase2_Lazar_Begin", 0.047f, true, 6, 8);
	ShipRenderer->CreateAnimation(PirateBossAniName::Ship_Phase2_LazarAtt_ChargingEnd, "Ship_phase2_Lazar_Begin", 0.047f, false, 9, 13);
	ShipRenderer->CreateAnimation(PirateBossAniName::Ship_Phase2_LazarAttack1, "Ship_Phase2_LazarShot", 0.047f, false);
	ShipRenderer->CreateAnimation(PirateBossAniName::Ship_Phase2_LazarAttack2, "Ship_Phase2_LazarShot", 0.047f, true, 1, 4);
	ShipRenderer->CreateAnimation(PirateBossAniName::Ship_Phase2_LazarAttack_End, "Ship_Phase2_LazarShot", 0.065f, false, 4, 5);


	// Uvula
	UvulaRenderer->CreateAnimation(PirateBossAniName::Uvula_Idle, "Uvula_Idle", 0.047f);
	UvulaRenderer->CreateAnimation(PirateBossAniName::Uvula_Shoot, "Uvula_Shoot", 0.047f, false);

	// other
	JawRenderer->CreateAnimation(PirateBossAniName::Ship_Phase2_JawIdle, "Ship_Phase2_JawIdle", 0.047f);
}

void ACaptainBrineybeardPhase2::SetAnimationCallback()
{
	// Ship
	ShipRenderer->SetLastFrameCallback(PirateBossAniName::Ship_Phase2_Transform_End, [this]()
		{
			ShipState.ChangeState(PirateBossState::Ship_Phase2_Idle);
		});
	ShipRenderer->SetLastFrameCallback(PirateBossAniName::Ship_Phase2_LazarAtt_Begin, [this]()
		{
			ShipState.ChangeState(PirateBossState::Ship_phase2_LazarAtt_Charging);
		});
	ShipRenderer->SetLastFrameCallback(PirateBossAniName::Ship_Phase2_LazarAtt_ChargingEnd, [this]()
		{
			ShipState.ChangeState(PirateBossState::Ship_phase2_LazarAttack);
		});
	ShipRenderer->SetLastFrameCallback(PirateBossAniName::Ship_Phase2_LazarAttack1, [this]()
		{
			ShipRenderer->ChangeAnimation(PirateBossAniName::Ship_Phase2_LazarAttack2);
		});
	ShipRenderer->SetLastFrameCallback(PirateBossAniName::Ship_Phase2_LazarAttack_End, [this]()
		{
			ShipState.ChangeState(PirateBossState::Ship_Phase2_Idle);
		});

	// Uvula
	UvulaRenderer->SetLastFrameCallback(PirateBossAniName::Uvula_Shoot, [this]()
		{
			UvulaRenderer->ChangeAnimation(PirateBossAniName::Uvula_Idle);
		});

}