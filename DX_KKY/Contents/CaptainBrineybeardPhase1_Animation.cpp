#include "PreCompile.h"

#include "CaptainBrineybeardPhase1.h"



void ACaptainBrineybeardPhase1::CreateAnimation()
{
	// Ship
	ShipRailRenderer->CreateAnimation(PirateBossAniName::Ship_Rail, "Ship_Rail", 0.065f);
	ShipMastRenderer->SetSprite("Ship_Mast.png");
	ShipSailRenderer->CreateAnimation(PirateBossAniName::Ship_Sail, "Ship_Sail", 0.05f);
	
	ShipRenderer->CreateAnimation(PirateBossAniName::Ship_Phase1_Idle, "Ship_Phase1_Idle", 0.065f);
	ShipRenderer->CreateAnimation(PirateBossAniName::Ship_Phase1_Blink, "Ship_Phase1_Blink", 0.065f, false);
	ShipRenderer->CreateAnimation(PirateBossAniName::Ship_Phase1_CannonAtt, "Ship_Phase1_ShootCannonBall", 0.065f, false);
	ShipRenderer->CreateAnimation(PirateBossAniName::Ship_Phase1_Wince_Begin, "Ship_Phase1_Wince", 0.065f, false, 0, 1);
	ShipRenderer->CreateAnimation(PirateBossAniName::Ship_Phase1_Wince_Idle, "Ship_Phase1_Wince", 0.065f, true, 1, 8);
	ShipRenderer->CreateAnimation(PirateBossAniName::Ship_Transform_Begin, "Ship_Transform", 0.065f, false, 0, 9);

	// Pirate
	PirateRenderer->CreateAnimation(PirateBossAniName::Pirate_Intro, "Pirate_Intro", 0.067f, true, 0, 4);
	PirateRenderer->CreateAnimation(PirateBossAniName::Pirate_Laugh, "Pirate_Intro",
		{ 0.047f,  0.047f , 0.047f , 0.047f , 0.047f , 0.047f , 0.047f , 0.047f , 0.047f , 0.047f , 0.047f , 0.047f},
		{ 4, 5, 6, 7, 8, 9, 10, 9, 8, 7, 6, 5 }, true);
	PirateRenderer->CreateAnimation(PirateBossAniName::Pirate_StopLaugh, "Pirate_Intro", { 0.067f ,0.067f ,0.067f }, { 11, 12, 13 }, false);
	PirateRenderer->CreateAnimation(PirateBossAniName::Pirate_Idle, "Pirate_Idle", 0.047f);
	PirateRenderer->CreateAnimation(PirateBossAniName::OctopusShoot_Begin, "Pirate_PickUp_Octopus", 0.047f, false);
	PirateRenderer->CreateAnimation(PirateBossAniName::OctopusShoot_Idle, "Pirate_Idle_Octopus", 0.057f);
	PirateRenderer->CreateAnimation(PirateBossAniName::OctopusShoot_Attack, "Pirate_Octopus_Attack", 0.034f, false);
	PirateRenderer->CreateAnimation(PirateBossAniName::OctopusShoot_End, "Pirate_PutDown_Octopus", 0.047f, false);
	PirateRenderer->CreateAnimation(PirateBossAniName::Pirate_Whistle, "Pirate_Whistle", 0.047f, false);

	PirateTopRenderer->CreateAnimation(PirateBossAniName::OctopusShoot_Begin_Top, "Pirate_PickUp_Octopus_Top", 0.047f, false);
	PirateTopRenderer->CreateAnimation(PirateBossAniName::OctopusShoot_Idle_Top, "Pirate_Idle_Octopus_Top", 0.057f);
	PirateTopRenderer->CreateAnimation(PirateBossAniName::OctopusShoot_Attack_Top, "Pirate_Octopus_Attack_Top", 0.034f, false);
	PirateTopRenderer->CreateAnimation(PirateBossAniName::OctopusShoot_End_Top, "Pirate_PutDown_Octopus_Top", 0.047f, false);


	// Animation Change
	ShipRailRenderer->ChangeAnimation(PirateBossAniName::Ship_Rail);
	ShipSailRenderer->ChangeAnimation(PirateBossAniName::Ship_Sail);
}

void ACaptainBrineybeardPhase1::SetAnimationCallback()
{
	// ship
	{
		ShipRenderer->SetFrameCallback(PirateBossAniName::Ship_Phase1_Blink, 7, [this]()
			{
				ShipState.ChangeState(PirateBossState::Ship_Phase1_Idle);
			});
		ShipRenderer->SetFrameCallback(PirateBossAniName::Ship_Phase1_CannonAtt, 29, [this]()
			{
				ShipState.ChangeState(PirateBossState::Ship_Phase1_Idle);
			});
		ShipRenderer->SetFrameCallback(PirateBossAniName::Ship_Phase1_CannonAtt, 19, [this]()
			{
				CreateCannonBall();
			});
		ShipRenderer->SetFrameCallback(PirateBossAniName::Ship_Phase1_Wince_Begin, 2, [this]()
			{
				ShipRenderer->ChangeAnimation(PirateBossAniName::Ship_Phase1_Wince_Idle);
			});
		ShipRenderer->SetFrameCallback(PirateBossAniName::Ship_Transform_Begin, 4, [this]()
			{
				Phase1_EndSetting();
			});
		ShipRenderer->SetFrameCallback(PirateBossAniName::Ship_Transform_Begin, 9, [this]()
			{
				// 페이즈 종료 신호 보내기
				SetIsPhaseEnd(true);
				return;
			});
	}


	// Pirate
	{
		PirateRenderer->SetFrameCallback(PirateBossAniName::Pirate_StopLaugh, 3, [this]()
			{
				PirateState.ChangeState(PirateBossState::Pirate_Idle);
			});
		PirateRenderer->SetFrameCallback(PirateBossAniName::OctopusShoot_Begin, 21, [this]()
			{
				PirateState.ChangeState(PirateBossState::OctopusShoot_Idle);
			});
		PirateRenderer->SetFrameCallback(PirateBossAniName::OctopusShoot_Attack, 19, [this]()
			{
				PirateState.ChangeState(PirateBossState::OctopusShoot_Idle);
			});
		PirateRenderer->SetFrameCallback(PirateBossAniName::OctopusShoot_Begin, 16, [this]()
			{
				PirateTopRenderer->SetActive(true);
				PirateTopRenderer->ChangeAnimation(PirateBossAniName::OctopusShoot_Begin_Top);
			});
		PirateRenderer->SetFrameCallback(PirateBossAniName::OctopusShoot_End, 13, [this]()
			{
				PirateState.ChangeState(PirateBossState::Pirate_Idle);
			});
		PirateRenderer->SetFrameCallback(PirateBossAniName::OctopusShoot_Attack, 9, [this]()
			{
				CreateOctopusBullet();
			});
		PirateRenderer->SetFrameCallback(PirateBossAniName::Pirate_Whistle, 50, [this]()
			{
				PirateState.ChangeState(PirateBossState::Pirate_Idle);
			});
		PirateRenderer->SetFrameCallback(PirateBossAniName::Pirate_Whistle, 30, [this]()
			{
				int RandomVal = UMath::RandomReturnInt(0, 1);

				switch (RandomVal)
				{
				case 0:
					SpawnShark();
					break;
				case 1:
					SpawnSeaDogs();
					break;
				default:
					MsgBoxAssert("존재할 수 없는 랜덤 값입니다." + std::to_string(RandomVal));
					return;
				}

				CreateWhistleEffect();
			});

		PirateTopRenderer->SetFrameCallback(PirateBossAniName::OctopusShoot_End_Top, 8, [this]()
			{
				PirateTopRenderer->SetActive(false);
			});

	}
}