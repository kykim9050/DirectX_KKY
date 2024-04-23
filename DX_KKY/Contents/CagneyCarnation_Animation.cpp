#include "PreCompile.h"

#include "CagneyCarnation.h"
#include "Acorn.h"
#include "FXUnit.h"


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



}

void ACagneyCarnation::SetAnimationCallback()
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
			int Case = UMath::GetInst().RandomReturnInt(0, 1);

			switch (Case)
			{
			case 0:
			{
				KindOfObject = EKindOfCreateObj::Boomerang;
				CreateObjectDelay = 2.0f;
				CreateObjectDelayInit = 2.0f;
				break;
			}
			case 1:
			{
				KindOfObject = EKindOfCreateObj::Acorn;
				CreateObjectDelay = 3.0f;
				CreateObjectDelayInit = 3.0f;

				for (int i = 0; i < AcornNum; i++)
				{
					AAcorn* NewAcorn = GetWorld()->SpawnActor<AAcorn>("Acorn").get();

					//Acorns.push_back(NewAcorn);
					NewAcorn->SetActorLocation(GColliderPosInfo::AcornInitPos[i]);
					NewAcorn->DelayCallBack(1.0f + 0.5f * i, [NewAcorn]()
						{
							NewAcorn->Shoot();
						});
				}

				break;
			}
			default:
				MsgBoxAssert("나올 수 없는 int형 랜덤 정수 입니다." + std::to_string(Case));
				return;
			}


		
			// 부메랑이던지 도토리 미사일이던지 전부다 적용되는 효과
			AFXUnit* CreateEffect = GetWorld()->SpawnActor<AFXUnit>("CreateEffect").get();
			CreateEffect->CreateAnimation(FAniInfo(FlowerBossAniName::Flower_CreateObject_Effect, GSpriteName::Flower_CreateObject_Effect, 0.033f), false);
			CreateEffect->SetRendererFrameCallback(FlowerBossAniName::Flower_CreateObject_Effect, 15, [CreateEffect]()
				{
					CreateEffect->Destroy();
				});
			CreateEffect->SetActorLocation(GColliderPosInfo::AcornInitPos[2]);
			CreateEffect->SetRendererAutoSize();
			CreateEffect->SetRendererOrder(ERenderingOrder::MonsterBulletFX);
			CreateEffect->ChangeAnimation(FlowerBossAniName::Flower_CreateObject_Effect);
		
		});
}
