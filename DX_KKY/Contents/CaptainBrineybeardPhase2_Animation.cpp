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
	ShipRenderer->CreateAnimation(PirateBossAniName::Ship_Phase2_LazarAttack1, "Ship_Phase2_LazarShot", 0.047f, false, 0, 4);
	ShipRenderer->CreateAnimation(PirateBossAniName::Ship_Phase2_LazarAttack2, "Ship_Phase2_LazarShot", 0.047f, true, 1, 4);
	ShipRenderer->CreateAnimation(PirateBossAniName::Ship_Phase2_LazarAttack_End, "Ship_Phase2_LazarShot", 0.067f, false, 5, 5);


	// Uvula
	UvulaRenderer->CreateAnimation(PirateBossAniName::Uvula_Idle, "Uvula_Idle", 0.047f);
	UvulaRenderer->CreateAnimation(PirateBossAniName::Uvula_Shoot, "Uvula_Shoot", 0.053f, false);

	// other
	JawRenderer->CreateAnimation(PirateBossAniName::Ship_Phase2_JawIdle, "Ship_Phase2_JawIdle", 0.047f);
	LazarRenderer->CreateAnimation(PirateBossAniName::Ship_Phase2_Lazar_Begin, "Ship_Lazar", 0.047f, false, 0, 2);
	LazarRenderer->CreateAnimation(PirateBossAniName::Ship_Phase2_Lazar_Idle, "Ship_Lazar", 0.047f, true, 3, 6);
	LazarRenderer->CreateAnimation(PirateBossAniName::Ship_Phase2_Lazar_End, "Ship_Lazar", 0.047f, false, 2, 0);

}

void ACaptainBrineybeardPhase2::SetAnimationCallback()
{
	// Ship
	ShipRenderer->SetFrameCallback(PirateBossAniName::Ship_Phase2_Transform_End, 7, [this]()
		{
			ShipState.ChangeState(PirateBossState::Ship_Phase2_Idle);
		});
	ShipRenderer->SetFrameCallback(PirateBossAniName::Ship_Phase2_LazarAtt_Begin, 6, [this]()
		{
			ShipState.ChangeState(PirateBossState::Ship_phase2_LazarAtt_Charging);
		});
	ShipRenderer->SetFrameCallback(PirateBossAniName::Ship_Phase2_LazarAtt_ChargingEnd, 5, [this]()
		{
			ShipState.ChangeState(PirateBossState::Ship_phase2_LazarAttack);
		});
	ShipRenderer->SetFrameCallback(PirateBossAniName::Ship_Phase2_LazarAttack1, 5, [this]()
		{
			ShipRenderer->ChangeAnimation(PirateBossAniName::Ship_Phase2_LazarAttack2);
		});
	ShipRenderer->SetFrameCallback(PirateBossAniName::Ship_Phase2_LazarAttack_End, 1,[this]()
		{
			ShipState.ChangeState(PirateBossState::Ship_Phase2_Idle);
		});

	// Uvula
	UvulaRenderer->SetFrameCallback(PirateBossAniName::Uvula_Shoot, 13, [this]()
		{
			UvulaRenderer->ChangeAnimation(PirateBossAniName::Uvula_Idle);
		});

	// Other
	LazarRenderer->SetFrameCallback(PirateBossAniName::Ship_Phase2_Lazar_Begin, 3, [this]()
		{
			LazarCollider->SetActive(true);
			LazarRenderer->ChangeAnimation(PirateBossAniName::Ship_Phase2_Lazar_Idle);
		});
	LazarRenderer->SetFrameCallback(PirateBossAniName::Ship_Phase2_Lazar_End, 3, [this]()
		{
			LazarRenderer->SetActive(false);
		});
}