#include "PreCompile.h"

#include "CaptainBrineybeardPhase1.h"
#include "OctopusBullet.h"
#include "CannonBall.h"

void ACaptainBrineybeardPhase1::CreateAnimation()
{
	// Ship
	ShipRailRenderer->CreateAnimation(PirateBossAniName::Ship_Rail, "Ship_Rail", 0.065f);
	ShipMastRenderer->SetSprite("Ship_Mast.png");
	ShipSailRenderer->CreateAnimation(PirateBossAniName::Ship_Sail, "Ship_Sail", 0.05f);
	
	ShipRenderer->CreateAnimation(PirateBossAniName::Ship_Phase1_Idle, "Ship_Phase1_Idle", 0.065f);
	ShipRenderer->CreateAnimation(PirateBossAniName::Ship_Phase1_Blink, "Ship_Phase1_Blink", 0.065f, false);
	ShipRenderer->CreateAnimation(PirateBossAniName::Ship_Phase1_CannonAtt, "Ship_Phase1_ShootCannonBall", 0.065f, false);


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
		ShipRenderer->SetLastFrameCallback(PirateBossAniName::Ship_Phase1_Blink, [this]()
			{
				ShipState.ChangeState(PirateBossState::Ship_Phase1_Idle);
				//ShipRenderer->ChangeAnimation(PirateBossAniName::Ship_Phase1_Idle);
			});
		ShipRenderer->SetLastFrameCallback(PirateBossAniName::Ship_Phase1_CannonAtt, [this]()
			{
				ShipState.ChangeState(PirateBossState::Ship_Phase1_Idle);
			});
		ShipRenderer->SetFrameCallback(PirateBossAniName::Ship_Phase1_CannonAtt, 19, [this]()
			{
				ACannonBall* CannonBall = GetWorld()->SpawnActor<ACannonBall>("ACannonBall", static_cast<int>(EActorType::MonsterBullet)).get();
				CannonBall->SetActorLocation(GetActorLocation() + GActorPosValue::CannonBall_RelativePos);
			});
	}


	// Pirate
	{
		PirateRenderer->SetLastFrameCallback(PirateBossAniName::Pirate_StopLaugh, [this]()
			{
				PirateState.ChangeState(PirateBossState::Pirate_Idle);
			});
		PirateRenderer->SetLastFrameCallback(PirateBossAniName::OctopusShoot_Begin, [this]()
			{
				PirateState.ChangeState(PirateBossState::OctopusShoot_Idle);
			});
		PirateRenderer->SetLastFrameCallback(PirateBossAniName::OctopusShoot_Attack, [this]()
			{
				PirateState.ChangeState(PirateBossState::OctopusShoot_Idle);
			});
		PirateRenderer->SetFrameCallback(PirateBossAniName::OctopusShoot_Begin, 16, [this]()
			{
				PirateTopRenderer->SetActive(true);
				PirateTopRenderer->ChangeAnimation(PirateBossAniName::OctopusShoot_Begin_Top);
			});
		PirateRenderer->SetLastFrameCallback(PirateBossAniName::OctopusShoot_End, [this]()
			{
				PirateState.ChangeState(PirateBossState::Pirate_Idle);
			});
		PirateRenderer->SetFrameCallback(PirateBossAniName::OctopusShoot_Attack, 9, [this]()
			{
				AOctopusBullet* NewOctoBullet = GetWorld()->SpawnActor<AOctopusBullet>("NewOctoBullet", static_cast<int>(EActorType::MonsterBullet)).get();
				NewOctoBullet->SetActorLocation(GetActorLocation() + GActorPosValue::OctoBullet_RelativePos);
			});
		PirateRenderer->SetLastFrameCallback(PirateBossAniName::Pirate_Whistle, [this]()
			{
				PirateState.ChangeState(PirateBossState::Pirate_Idle);
			});
		PirateRenderer->SetFrameCallback(PirateBossAniName::Pirate_Whistle, 30, [this]()
			{
				CreateWhistleEffect();
			});

		PirateTopRenderer->SetLastFrameCallback(PirateBossAniName::OctopusShoot_End_Top, [this]()
			{
				PirateTopRenderer->SetActive(false);
			});

	}
}