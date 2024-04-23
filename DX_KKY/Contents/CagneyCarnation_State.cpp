#include "PreCompile.h"
#include "CagneyCarnation.h"

#include "FXBase.h"
#include "Seed.h"
#include "Acorn.h"

void ACagneyCarnation::StateInit()
{
	StateCreate();
	StartFunctionSet();
	UpdateFunctionSet();
	EndFunctionSet();

	//State.ChangeState(FlowerBossState::Intro);
	State.ChangeState(FlowerBossState::CreateObject_Begin);
}


void ACagneyCarnation::StateCreate()
{
	// Intro
	// Idle
	State.CreateState(FlowerBossState::Intro);
	State.CreateState(FlowerBossState::Idle);

	// FaceAttack
	State.CreateState(FlowerBossState::FaceAttackHigh_Begin);
	State.CreateState(FlowerBossState::FaceAttackHigh_Idle);
	State.CreateState(FlowerBossState::FaceAttackHigh_End);
	InsertAttackPattern(EAttackPattern::FaceAttack_High, FlowerBossState::FaceAttackHigh_Begin);
	State.CreateState(FlowerBossState::FaceAttackLow_Begin);
	State.CreateState(FlowerBossState::FaceAttackLow_Idle);
	State.CreateState(FlowerBossState::FaceAttackLow_End);
	InsertAttackPattern(EAttackPattern::FaceAttack_Low, FlowerBossState::FaceAttackLow_Begin);

	// Gatling
	State.CreateState(FlowerBossState::Gatling_Begin);
	State.CreateState(FlowerBossState::Gatling_Idle);
	State.CreateState(FlowerBossState::Gatling_End);
	InsertAttackPattern(EAttackPattern::Gatling, FlowerBossState::Gatling_Begin);

	// Create Object
	State.CreateState(FlowerBossState::CreateObject_Begin);
	State.CreateState(FlowerBossState::CreateObject_Idle);
	State.CreateState(FlowerBossState::CreateObject_End);
	State.CreateState(FlowerBossState::CreateObject_Release);
	State.CreateState(FlowerBossState::CreateObject_ReleaseIdle);
	State.CreateState(FlowerBossState::CreateObject_ReleaseRev);
	InsertAttackPattern(EAttackPattern::CreateObject, FlowerBossState::CreateObject_Begin);
}

void ACagneyCarnation::StartFunctionSet()
{
	//Intro
	State.SetStartFunction(FlowerBossState::Intro, [this]()
		{
			Renderer->ChangeAnimation(FlowerBossAniName::Flower_Intro);
		});

	//Idle
	State.SetStartFunction(FlowerBossState::Idle, [this]()
		{
			Renderer->ChangeAnimation(FlowerBossAniName::Flower_Idle);
		});

	// FaceAttack
	State.SetStartFunction(FlowerBossState::FaceAttackHigh_Begin, [this]()
		{
			Renderer->ChangeAnimation(FlowerBossAniName::Flower_FaceAttackHigh_Begin);
		});
	State.SetStartFunction(FlowerBossState::FaceAttackHigh_Idle, [this]()
		{
			FaceAttHighCollider->SetActive(true);
			Renderer->ChangeAnimation(FlowerBossAniName::Flower_FaceAttackHigh_Idle);
		});
	State.SetStartFunction(FlowerBossState::FaceAttackHigh_End, [this]()
		{
			FaceAttHighCollider->SetActive(false);
			Renderer->ChangeAnimation(FlowerBossAniName::Flower_FaceAttackHigh_End);
		});

	State.SetStartFunction(FlowerBossState::FaceAttackLow_Begin, [this]()
		{
			AddActorLocation(FVector(0.0f, -110.f, 0.0f));
			FaceAttLowCollider->AddPosition(FVector(0.0f, 110.f, 0.0f));
			Renderer->ChangeAnimation(FlowerBossAniName::Flower_FaceAttackLow_Begin);
		});
	State.SetStartFunction(FlowerBossState::FaceAttackLow_Idle, [this]()
		{
			FaceAttLowCollider->SetActive(true);
			Renderer->ChangeAnimation(FlowerBossAniName::Flower_FaceAttackLow_Idle);
		});
	State.SetStartFunction(FlowerBossState::FaceAttackLow_End, [this]()
		{
			FaceAttLowCollider->SetActive(false);
			Renderer->ChangeAnimation(FlowerBossAniName::Flower_FaceAttackLow_End);
		});

	// Gatling
	State.SetStartFunction(FlowerBossState::Gatling_Begin, [this]()
		{
			Renderer->ChangeAnimation(FlowerBossAniName::Flower_Gatling_Begin);
		});
	State.SetStartFunction(FlowerBossState::Gatling_Idle, [this]()
		{
			std::vector<ASeed*> Seeds = std::vector<ASeed*>();

			float SeedRandXPos = 0.0f;

			for (int i = 0; i < SeedNum; i++)
			{
				ASeed* NewSeed = GetWorld()->SpawnActor<ASeed>("NewSeed").get();
				Seeds.push_back(NewSeed);

				SeedRandXPos = UMath::GetInst().RandomReturnFloat(FlowerBossStageValue::SeedInitMinXPos, FlowerBossStageValue::SeedInitMaxXPos);

				Seeds[i]->SetActorLocation(float4(SeedRandXPos, FlowerBossStageValue::SeedInitYPos + FlowerBossStageValue::SeedFallInter * i, 0.0f));
			}
			// 파랑 2개, 보라 2개, 분홍 1개 씨앗 생성
			Seeds[0]->SetColor(ESeedColor::Blue);
			Seeds[1]->SetColor(ESeedColor::Purple);
			Seeds[2]->SetColor(ESeedColor::Pink);
			Seeds[3]->SetColor(ESeedColor::Blue);
			Seeds[4]->SetColor(ESeedColor::Purple);
			
			// 색깔별로 떨어지는 것 랜더링 해야 하고
			// 5개만 딱 만들어야 하고
			// 떨어지는 상태 (가운데 피봇), 떨어져서 바닥에 닿아서 심어질 때 (바텀 피봇) 

			Renderer->ChangeAnimation(FlowerBossAniName::Flower_Gatling_Idle);
		});
	State.SetStartFunction(FlowerBossState::Gatling_End, [this]()
		{
			Renderer->ChangeAnimation(FlowerBossAniName::Flower_Gatling_End);
		});

	// Create Object
	State.SetStartFunction(FlowerBossState::CreateObject_Begin, [this]()
		{
			Renderer->ChangeAnimation(FlowerBossAniName::Flower_CreateObject_Begin);
		});
	State.SetStartFunction(FlowerBossState::CreateObject_Idle, [this]()
		{
			Renderer->ChangeAnimation(FlowerBossAniName::Flower_CreateObject_Idle);
		});
	State.SetStartFunction(FlowerBossState::CreateObject_End, [this]()
		{
			Renderer->ChangeAnimation(FlowerBossAniName::Flower_CreateObject_End);
		});
	State.SetStartFunction(FlowerBossState::CreateObject_Release, [this]()
		{
			Renderer->ChangeAnimation(FlowerBossAniName::Flower_CreateObject_Release);
		});
	State.SetStartFunction(FlowerBossState::CreateObject_ReleaseIdle, [this]()
		{
			// 생성된 CreateObject의 종류에 따라서 활성화 시키는 대상이 다르게 만든다.

			Renderer->ChangeAnimation(FlowerBossAniName::Flower_CreateObject_ReleaseIdle);
		});
	State.SetStartFunction(FlowerBossState::CreateObject_ReleaseRev, [this]()
		{
			Renderer->ChangeAnimation(FlowerBossAniName::Flower_CreateObject_ReleaseRev);
		});


}

void ACagneyCarnation::UpdateFunctionSet()
{
	// Idle
	State.SetUpdateFunction(FlowerBossState::Idle, std::bind(&ACagneyCarnation::Idle, this, std::placeholders::_1));

	//Intro
	State.SetUpdateFunction(FlowerBossState::Intro, [this](float){});

	// FaceAttack
	State.SetUpdateFunction(FlowerBossState::FaceAttackHigh_Begin, [this](float){});
	State.SetUpdateFunction(FlowerBossState::FaceAttackHigh_Idle, std::bind(&ACagneyCarnation::FaceAttackHigh_Idle, this, std::placeholders::_1));
	State.SetUpdateFunction(FlowerBossState::FaceAttackHigh_End, [this](float){});
	State.SetUpdateFunction(FlowerBossState::FaceAttackLow_Begin, [this](float){});
	State.SetUpdateFunction(FlowerBossState::FaceAttackLow_Idle, std::bind(&ACagneyCarnation::FaceAttackLow_Idle, this, std::placeholders::_1));
	State.SetUpdateFunction(FlowerBossState::FaceAttackLow_End, [this](float) {});

	// Gatling
	State.SetUpdateFunction(FlowerBossState::Gatling_Begin, [this](float) {});
	State.SetUpdateFunction(FlowerBossState::Gatling_Idle, std::bind(&ACagneyCarnation::Gatling_Idle, this, std::placeholders::_1));
	State.SetUpdateFunction(FlowerBossState::Gatling_End, [this](float) {});

	// Create Obeject
	State.SetUpdateFunction(FlowerBossState::CreateObject_Begin, [this](float) {});
	State.SetUpdateFunction(FlowerBossState::CreateObject_Idle, std::bind(&ACagneyCarnation::CreateObject_Idle, this, std::placeholders::_1));
	State.SetUpdateFunction(FlowerBossState::CreateObject_Release, [this](float) {});
	State.SetUpdateFunction(FlowerBossState::CreateObject_ReleaseIdle, std::bind(&ACagneyCarnation::CreateObject_ReleaseIdle, this, std::placeholders::_1));
	State.SetUpdateFunction(FlowerBossState::CreateObject_ReleaseRev, [this](float) {});
	State.SetUpdateFunction(FlowerBossState::CreateObject_End, [this](float) {});
}

void ACagneyCarnation::EndFunctionSet()
{
	State.SetEndFunction(FlowerBossState::Gatling_Idle, [this]()
		{
			MissileLaunchTIme = 0.0f;
		});
}

void ACagneyCarnation::Idle(float _DeltaTime)
{
	P1_ChangeDelay -= _DeltaTime;

	if (0.0f >= P1_ChangeDelay)
	{
		P1_ChangeDelay = P1_ChangeDelayValue;

		int PatternNum = UMath::GetInst().RandomReturnIntEnum(0, EAttackPattern::Max);


		State.ChangeState(AttackPattern[PatternNum]);
		return;
	}
}

void ACagneyCarnation::FaceAttackHigh_Idle(float _DeltaTime)
{
	FaceAttackDelay -= _DeltaTime;

	if (0.0f >= FaceAttackDelay)
	{
		FaceAttackDelay = FaceAttackDelayValue;
		State.ChangeState(FlowerBossState::FaceAttackHigh_End);
		return;
	}
}

void ACagneyCarnation::FaceAttackLow_Idle(float _DeltaTime)
{
	FaceAttackDelay -= _DeltaTime;

	if (0.0f >= FaceAttackDelay)
	{
		FaceAttackDelay = FaceAttackDelayValue;
		State.ChangeState(FlowerBossState::FaceAttackLow_End);
		return;
	}
}

void ACagneyCarnation::Gatling_Idle(float _DeltaTime)
{
	GatlingTime -= _DeltaTime;
	MissileLaunchTIme -= _DeltaTime;

	if (0.0f >= MissileLaunchTIme)
	{
		MissileLaunchTIme = MissileLaunchTImeValue;

		std::shared_ptr<AFXBase> Missile = GetWorld()->SpawnActor<AFXBase>("Missile");

		int RandomCase = UMath::GetInst().RandomReturnInt(0, 1);
		float RandomDegree = UMath::GetInst().RandomReturnFloat(-10.0f, 10.0f);

		switch (RandomCase)
		{
		case 0:
			Missile->FXInit(ERenderingOrder::BossMonsterBackFX2, FAniInfo(FlowerBossAniName::BlueMissile, "GatlingMissileBlue", 0.05f));
			Missile->SetActorLocation(GRendererPos::FlowerBoss_MissileInitPos);
			Missile->SetActorRotation(float4(0.0f, 0.0f, RandomDegree));
			Missile->SetImgPivot(EPivot::BOT);
			break;
		case 1:
			Missile->FXInit(ERenderingOrder::BossMonsterBackFX2, FAniInfo(FlowerBossAniName::PurleMissile, "GatlingMissilePurple", 0.05f));
			Missile->SetActorLocation(GRendererPos::FlowerBoss_MissileInitPos);
			Missile->SetActorRotation(float4(0.0f, 0.0f, RandomDegree));
			Missile->SetImgPivot(EPivot::BOT);
			break;
		default:
			break;
		}

		if (0.0f >= GatlingTime)
		{
			GatlingTime = GatlingTimeValue;
			State.ChangeState(FlowerBossState::Gatling_End);
			return;
		}
	}
}

void ACagneyCarnation::CreateObject_Idle(float _DeltaTime)
{
	CreateObjectTime -= _DeltaTime;

	if (0.0f >= CreateObjectTime)
	{
		CreateObjectTime = 1.0f;

		State.ChangeState(FlowerBossState::CreateObject_Release);
		return;
	}
}

void ACagneyCarnation::CreateObject_ReleaseIdle(float _DeltaTime)
{
	CreateObjectReleaseTime -= _DeltaTime;

	if (0.0f >= CreateObjectReleaseTime)
	{
		CreateObjectReleaseTime = 1.0f;

		// 난수 받아서 다시 어떤걸 실행시킬지 결정
		int RandomValue = UMath::GetInst().RandomReturnInt(0, 1);

		switch (RandomValue)
		{
		case 0:
			State.ChangeState(FlowerBossState::CreateObject_ReleaseRev);
			break;
		case 1:
			State.ChangeState(FlowerBossState::CreateObject_End);
			break;
		default:
			MsgBoxAssert("리턴될 수 없는 Random Int 값입니다.");
			break;
		}
		return;
	}
}