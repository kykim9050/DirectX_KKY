#include "PreCompile.h"

#include "CagneyCarnation.h"
#include "Pollen.h"

void ACagneyCarnation::AnimationInit()
{
	CreateAnimation();
	SetAnimationCallback();

	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetPivot(EPivot::RIGHTBOTTOM);
	Renderer->SetOrder(ERenderingOrder::BossMonster);
}

void ACagneyCarnation::CreateAnimation()
{
	// BottomIvyRenderer
	{
		BottomIvyRenderer->CreateAnimation(FlowerBossAniName::BottomIvy_Spawn, "Ivy_Main", 0.0416f, false);
		BottomIvyRenderer->CreateAnimation(FlowerBossAniName::BottomIvy_Idle, "Ivy_MainIdle", 0.1f);
	}

	// Main Renderer
	{
		Renderer->CreateAnimation(FlowerBossAniName::Flower_Idle, "FlowerIdle", 0.0416f);
		Renderer->CreateAnimation(FlowerBossAniName::Flower_Intro, "FlowerIntro", 0.0416f, false);

		// Face Attack
		Renderer->CreateAnimation(FlowerBossAniName::Flower_FaceAttackHigh_Begin, "FaceAttackHighBegin", 0.0416f, false);
		Renderer->CreateAnimation(FlowerBossAniName::Flower_FaceAttackHigh_Idle, "FaceAttackHighIdle", 0.067f);
		Renderer->CreateAnimation(FlowerBossAniName::Flower_FaceAttackHigh_End, "FaceAttackHighEnd", 0.067f, false);
		Renderer->CreateAnimation(FlowerBossAniName::Flower_FaceAttackLow_Begin, "FaceAttackLowBegin", 0.0416f, false);
		Renderer->CreateAnimation(FlowerBossAniName::Flower_FaceAttackLow_Idle, "FaceAttackLowIdle", 0.067f);
		Renderer->CreateAnimation(FlowerBossAniName::Flower_FaceAttackLow_End, "FaceAttackLowEnd", 0.067f, false);

		// Gatling
		Renderer->CreateAnimation(FlowerBossAniName::Flower_Gatling_Begin, "GatlingBegin", 0.0416f, false);
		Renderer->CreateAnimation(FlowerBossAniName::Flower_Gatling_Idle, "GatlingIdle", 0.0416f);
		Renderer->CreateAnimation(FlowerBossAniName::Flower_Gatling_End, "GatlingEnd", 0.0416f, false);

		// Create Object
		Renderer->CreateAnimation(FlowerBossAniName::Flower_CreateObject_Begin, "CreateObjectBegin", 0.0416f, false);
		Renderer->CreateAnimation(FlowerBossAniName::Flower_CreateObject_Idle, "CreateObjectIdle", 0.0416f);
		Renderer->CreateAnimation(FlowerBossAniName::Flower_CreateObject_Release, "CreateObjectRelease", 0.0416f, false);
		Renderer->CreateAnimation(FlowerBossAniName::Flower_CreateObject_ReleaseIdle, "CreateObjectReleaseIdle", 0.0678f);
		Renderer->CreateAnimation(FlowerBossAniName::Flower_CreateObject_ReleaseRev, "CreateObjectRelease", 0.0416f, false, 6, 0);
		Renderer->CreateAnimation(FlowerBossAniName::Flower_CreateObject_End, "CreateObjectEnd", 0.0416f, false);

		// Phase2 Intro
		Renderer->CreateAnimation(FlowerBossAniName::FlowerP2_Intro1, "FlowerFinalIntro1", 0.0416f, false);
		Renderer->CreateAnimation(FlowerBossAniName::FlowerP2_Intro2, "FlowerFinalIntro2", 0.0416f);
		Renderer->CreateAnimation(FlowerBossAniName::FlowerP2_Intro3, "FlowerFinalIntro3", 0.0416f, false);
		Renderer->CreateAnimation(FlowerBossAniName::FlowerP2_Intro4, "FlowerFinalIntro4", 0.0416f);
		Renderer->CreateAnimation(FlowerBossAniName::FlowerP2_Intro5, "FlowerFinalIntro5", 0.0416f, false);

		// Phase2 Idle
		Renderer->CreateAnimation(FlowerBossAniName::FlowerP2_Idle, "FlowerFinal_Idle", 0.0416f);
	
		// Phase2 Spit
		Renderer->CreateAnimation(FlowerBossAniName::FlowerP2_Spit_Begin, "FlowerFinalSpitBegin", 0.0416f, false);
		Renderer->CreateAnimation(FlowerBossAniName::FlowerP2_Spit_End, "FlowerFinalSpitEnd", 0.0416f, false);
		
		// Dead
		Renderer->CreateAnimation(FlowerBossAniName::FlowerBoss_Death, "FlowerDeath", 0.0416f);
	}
}

void ACagneyCarnation::SetAnimationCallback()
{
	// BottomIvyRenderer
	{
		BottomIvyRenderer->SetFrameCallback(FlowerBossAniName::BottomIvy_Spawn, 21, [this]()
			{
				BottomIvyRenderer->ChangeAnimation(FlowerBossAniName::BottomIvy_Idle);
			});
	}

	// Main Renderer
	{
		// Intro
		Renderer->SetFrameCallback(FlowerBossAniName::Flower_Intro, 38, [this]()
			{
				State.ChangeState(FlowerBossState::Idle);
			});

		// Face Attack High
		Renderer->SetFrameCallback(FlowerBossAniName::Flower_FaceAttackHigh_Begin, 28, [this]()
			{
				State.ChangeState(FlowerBossState::FaceAttackHigh_Idle);
			});
		Renderer->SetFrameCallback(FlowerBossAniName::Flower_FaceAttackHigh_End, 5, [this]()
			{
				State.ChangeState(FlowerBossState::Idle);
			});
		Renderer->SetFrameCallback(FlowerBossAniName::Flower_FaceAttackLow_Begin, 28, [this]()
			{
				State.ChangeState(FlowerBossState::FaceAttackLow_Idle);
			});
		Renderer->SetFrameCallback(FlowerBossAniName::Flower_FaceAttackLow_End, 6, [this]()
			{
				AddActorLocation(FVector(0.0f, 110.f, 0.0f));
				FaceAttLowCollider->AddPosition(FVector(0.0f, -110.f, 0.0f));
				State.ChangeState(FlowerBossState::Idle);
			});

		// Gatling
		Renderer->SetFrameCallback(FlowerBossAniName::Flower_Gatling_Begin, 7, [this]()
			{
				State.ChangeState(FlowerBossState::Gatling_Idle);
			});
		Renderer->SetFrameCallback(FlowerBossAniName::Flower_Gatling_End, 7, [this]()
			{
				State.ChangeState(FlowerBossState::Idle);
			});

		// Create Obecjt
		Renderer->SetFrameCallback(FlowerBossAniName::Flower_CreateObject_Begin, 10, [this]()
			{
				State.ChangeState(FlowerBossState::CreateObject_Idle);
			});
		Renderer->SetFrameCallback(FlowerBossAniName::Flower_CreateObject_Release, 7, [this]()
			{
				State.ChangeState(FlowerBossState::CreateObject_ReleaseIdle);
			});
		Renderer->SetFrameCallback(FlowerBossAniName::Flower_CreateObject_ReleaseRev, 7, [this]()
			{
				State.ChangeState(FlowerBossState::CreateObject_Idle);
			});
		Renderer->SetFrameCallback(FlowerBossAniName::Flower_CreateObject_End, 5, [this]()
			{
				State.ChangeState(FlowerBossState::Idle);
			});
		Renderer->SetFrameCallback(FlowerBossAniName::Flower_CreateObject_Release, 3, [this]()
			{
				int Case = UMath::RandomReturnInt(0, 1);

				switch (Case)
				{
				case 0:
				{
					CreateBoomerang();
					CreateObjectDelay = 0.5f;
					CreateObjectDelayInit = 0.5f;
					break;
				}
				case 1:
				{
					CreateAcorn();
					CreateObjectDelay = 1.5f;
					CreateObjectDelayInit = 1.5f;

					break;
				}
				default:
					MsgBoxAssert("나올 수 없는 int형 랜덤 정수 입니다." + std::to_string(Case));
					return;
				}

				CreateObjectSpawnEffect();
			});

		// Phase2 Intro
		Renderer->SetFrameCallback(FlowerBossAniName::FlowerP2_Intro1, 5, [this]()
			{
				Renderer->ChangeAnimation(FlowerBossAniName::FlowerP2_Intro2);
			});
		Renderer->SetFrameCallback(FlowerBossAniName::FlowerP2_Intro3, 10, [this]()
			{
				Renderer->ChangeAnimation(FlowerBossAniName::FlowerP2_Intro4);
			});
		Renderer->SetFrameCallback(FlowerBossAniName::FlowerP2_Intro5, 17, [this]()
			{
				State.ChangeState(FlowerBossState::Phase2_Idle);
			});

		// Phase2 Spit
		Renderer->SetFrameCallback(FlowerBossAniName::FlowerP2_Spit_Begin, 11, [this]()
			{
				// 마지막에 Poll도 던지기
				APollen* NewPollen = GetWorld()->SpawnActor<APollen>("NewPollen").get();
				NewPollen->SetActorLocation(float4(1020.0f, -320.0f, 0.0f));

				Renderer->ChangeAnimation(FlowerBossAniName::FlowerP2_Spit_End);
			});
		Renderer->SetFrameCallback(FlowerBossAniName::FlowerP2_Spit_End, 11, [this]()
			{
				State.ChangeState(FlowerBossState::Phase2_Idle);
			});

	}
}
