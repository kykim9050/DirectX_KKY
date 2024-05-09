#include "PreCompile.h"
#include "CagneyCarnation.h"

#include "FXBase.h"
#include "Seed.h"
#include "Acorn.h"
#include "Vine.h"

void ACagneyCarnation::StateInit()
{
	StateCreate();
	StartFunctionSet();
	UpdateFunctionSet();
	EndFunctionSet();

	State.ChangeState(FlowerBossState::Intro);
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

	// Phase2 Intro
	State.CreateState(FlowerBossState::Phase2Intro_1);
	State.CreateState(FlowerBossState::Phase2Intro_2);
	State.CreateState(FlowerBossState::Phase2Intro_3);

	// Phase2 Idle
	State.CreateState(FlowerBossState::Phase2_Idle);

	// Phase2 Spit
	State.CreateState(FlowerBossState::Phase2_Spit);

	// Dead
	State.CreateState(FlowerBossState::FlowerBoss_Dead);
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
			HeadCollider->SetPosition(GColliderPosInfo::FlowerBoss_HeadColRelPos);
			Renderer->ChangeAnimation(FlowerBossAniName::Flower_Idle);
		});

	// FaceAttack
	State.SetStartFunction(FlowerBossState::FaceAttackHigh_Begin, [this]()
		{
			HeadCollider->SetPosition(GColliderPosInfo::FlowerBoss_FAH_HeadColRelPos);
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
			HeadCollider->SetPosition(GColliderPosInfo::FlowerBoss_FAL_HeadColRelPos);
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

				SeedRandXPos = UMath::RandomReturnFloat(FlowerBossStageValue::SeedInitMinXPos, FlowerBossStageValue::SeedInitMaxXPos);

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


	// Phase2 Intro
	State.SetStartFunction(FlowerBossState::Phase2Intro_1, [this]()
		{
			Renderer->ChangeAnimation(FlowerBossAniName::FlowerP2_Intro1);
		});
	State.SetStartFunction(FlowerBossState::Phase2Intro_2, [this]()
		{
			Renderer->ChangeAnimation(FlowerBossAniName::FlowerP2_Intro3);
		});
	State.SetStartFunction(FlowerBossState::Phase2Intro_3, [this]()
		{
			CreateBottomIvy();
			Renderer->ChangeAnimation(FlowerBossAniName::FlowerP2_Intro5);
		});

	// Phase2 Idle
	State.SetStartFunction(FlowerBossState::Phase2_Idle, [this]()
		{
			HeadCollider->SetPosition(GColliderPosInfo::FlowerBoss_P2_HeadColRelPos);
			Renderer->ChangeAnimation(FlowerBossAniName::FlowerP2_Idle);
		});

	// Phase2 Spit
	State.SetStartFunction(FlowerBossState::Phase2_Spit , [this]()
		{
			Renderer->ChangeAnimation(FlowerBossAniName::FlowerP2_Spit_Begin);
		});

	// Boss Dead
	State.SetStartFunction(FlowerBossState::FlowerBoss_Dead, [this]()
		{
			DelayCallBack(0.01f, []()
				{
					UEngineSound::SoundPlay("level_knockout_boom.wav");
				});

			HeadCollider->SetActive(false);
			FaceAttHighCollider->SetActive(false);
			FaceAttLowCollider->SetActive(false);
			BottomIvyCollider->SetActive(false);

			Renderer->ChangeAnimation(FlowerBossAniName::FlowerBoss_Death);
			SetIsPhaseEnd(true);

		});

}

void ACagneyCarnation::UpdateFunctionSet()
{
	// Idle
	State.SetUpdateFunction(FlowerBossState::Idle, std::bind(&ACagneyCarnation::Idle, this, std::placeholders::_1));

	//Intro
	State.SetUpdateFunction(FlowerBossState::Intro, [](float){});

	// FaceAttack
	State.SetUpdateFunction(FlowerBossState::FaceAttackHigh_Begin, [](float){});
	State.SetUpdateFunction(FlowerBossState::FaceAttackHigh_Idle, std::bind(&ACagneyCarnation::FaceAttackHigh_Idle, this, std::placeholders::_1));
	State.SetUpdateFunction(FlowerBossState::FaceAttackHigh_End, [](float){});
	State.SetUpdateFunction(FlowerBossState::FaceAttackLow_Begin, [](float){});
	State.SetUpdateFunction(FlowerBossState::FaceAttackLow_Idle, std::bind(&ACagneyCarnation::FaceAttackLow_Idle, this, std::placeholders::_1));
	State.SetUpdateFunction(FlowerBossState::FaceAttackLow_End, [](float) {});

	// Gatling
	State.SetUpdateFunction(FlowerBossState::Gatling_Begin, [](float) {});
	State.SetUpdateFunction(FlowerBossState::Gatling_Idle, std::bind(&ACagneyCarnation::Gatling_Idle, this, std::placeholders::_1));
	State.SetUpdateFunction(FlowerBossState::Gatling_End, [](float) {});

	// Create Obeject
	State.SetUpdateFunction(FlowerBossState::CreateObject_Begin, [](float) {});
	State.SetUpdateFunction(FlowerBossState::CreateObject_Idle, std::bind(&ACagneyCarnation::CreateObject_Idle, this, std::placeholders::_1));
	State.SetUpdateFunction(FlowerBossState::CreateObject_Release, [](float) {});
	State.SetUpdateFunction(FlowerBossState::CreateObject_ReleaseIdle, std::bind(&ACagneyCarnation::CreateObject_ReleaseIdle, this, std::placeholders::_1));
	State.SetUpdateFunction(FlowerBossState::CreateObject_ReleaseRev, [](float) {});
	State.SetUpdateFunction(FlowerBossState::CreateObject_End, [](float) {});

	// Phase2 Intro
	State.SetUpdateFunction(FlowerBossState::Phase2Intro_1, std::bind(&ACagneyCarnation::Phase2Intro_1, this, std::placeholders::_1));
	State.SetUpdateFunction(FlowerBossState::Phase2Intro_2, std::bind(&ACagneyCarnation::Phase2Intro_2, this, std::placeholders::_1));
	State.SetUpdateFunction(FlowerBossState::Phase2Intro_3, [](float) {});

	// Phase2 Idle
	State.SetUpdateFunction(FlowerBossState::Phase2_Idle, std::bind(&ACagneyCarnation::Phase2_Idle, this, std::placeholders::_1));

	// Phase2 Spit
	State.SetUpdateFunction(FlowerBossState::Phase2_Spit, [](float) {});

	// Dead
	State.SetUpdateFunction(FlowerBossState::FlowerBoss_Dead, std::bind(&ACagneyCarnation::Dead, this, std::placeholders::_1));
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
	if (-1 != PatternNum)
	{
		Dbg_PatternSwitchDelay -= _DeltaTime;

		if (0.0f >= Dbg_PatternSwitchDelay)
		{
			switch (PatternNum)
			{
			case static_cast<int>(EFlowerBossPattern::CreateObject):
				State.ChangeState(FlowerBossState::CreateObject_Begin);
				break;
			case static_cast<int>(EFlowerBossPattern::Gatling):
				State.ChangeState(FlowerBossState::Gatling_Begin);
				break;
			case static_cast<int>(EFlowerBossPattern::FaceAttack_High):
				State.ChangeState(FlowerBossState::FaceAttackHigh_Begin);
				break;
			case static_cast<int>(EFlowerBossPattern::FaceAttack_Low):
				State.ChangeState(FlowerBossState::FaceAttackLow_Begin);
				break;
			case static_cast<int>(EFlowerBossPattern::Phase2):
				State.ChangeState(FlowerBossState::Phase2Intro_1);
				break;
			default:
				MsgBoxAssert("지정되지 않은 패턴을 실행하려고 했습니다.");
				break;
			}

			Dbg_PatternSwitchDelay = Dbg_PatternSwitchDelayInit;
			PatternNum = -1;
			return;
		}
		return;
	}

	if (Phase2StartHP >= GetHp())
	{
		P2ChangeDelay -= _DeltaTime;

		if (0.0f >= P2ChangeDelay)
		{
			State.ChangeState(FlowerBossState::Phase2Intro_1);
			return;
		}

		return;
	}

	P1_ChangeDelay -= _DeltaTime;

	if (0.0f >= P1_ChangeDelay)
	{
		P1_ChangeDelay = P1_ChangeDelayValue;

		int PatternNum = UMath::RandomReturnIntEnum(0, EAttackPattern::Max);


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

		int RandomCase = UMath::RandomReturnInt(0, 1);
		float RandomDegree = UMath::RandomReturnFloat(-10.0f, 10.0f);

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
		CreateObjectTime = CreateObjectTimeInit;

		State.ChangeState(FlowerBossState::CreateObject_Release);
		return;
	}
}

void ACagneyCarnation::CreateObject_ReleaseIdle(float _DeltaTime)
{
	CreateObjectDelay -= _DeltaTime;

	if (0.0f >= CreateObjectDelay)
	{
		CreateObjectDelay = CreateObjectDelayInit;

		// 난수 받아서 다시 어떤걸 실행시킬지 결정
		int RandomValue = UMath::RandomReturnInt(0, 1);

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

void ACagneyCarnation::Phase2Intro_1(float _DeltaTime)
{
	P2ChangingDelay -= _DeltaTime;

	if (0.0f >= P2ChangingDelay)
	{
		P2ChangingDelay = 1.0f;
		State.ChangeState(FlowerBossState::Phase2Intro_2);
		return;
	}
}

void ACagneyCarnation::Phase2Intro_2(float _DeltaTime)
{
	P2ChangingDelay -= _DeltaTime;

	if (0.0f >= P2ChangingDelay)
	{
		P2ChangingDelay = 1.0f;
		State.ChangeState(FlowerBossState::Phase2Intro_3);
		return;
	}
}

void ACagneyCarnation::Phase2_Idle(float _DeltaTime)
{
	if (0.0f >= GetHp())
	{
		State.ChangeState(FlowerBossState::FlowerBoss_Dead);
		return;
	}

	int WaitVineNum = 0;

	for (int i = 0; i < VineNum; i++)
	{
		if (false == Vines[i]->IsWait())
		{
			continue;
		}

		++WaitVineNum;
	}

	if (3 == WaitVineNum)
	{
		CanCreateVine = true;
	}

	{
		std::string Msg = std::format("RestVine Num : {}\n", std::to_string(WaitVineNum));
		UEngineDebugMsgWindow::PushMsg(Msg);
	}


	if (true == CanCreateVine)
	{
		VineAttackDelay -= _DeltaTime;

		if (0.0f >= VineAttackDelay)
		{
			VineAttackDelay = VineAttackDelayInit;
			CanCreateVine = false;

			VineGrowUp();
		}
	}

	
	SpitDelay -= _DeltaTime;

	if (0.0f >= SpitDelay)
	{
		SpitDelay = SpitDelayInit;

		State.ChangeState(FlowerBossState::Phase2_Spit);
		return;
	}
}

void ACagneyCarnation::Dead(float _DeltaTime)
{
	ExplosionEffDelay -= _DeltaTime;
	
	if (0.0f >= ExplosionEffDelay)
	{
		ExplosionEffDelay = ExplosionEffDelayInit + ExplosionEffDelay;

		float RandomAngleValue = UMath::RandomReturnFloat(0.0f, 360.0f);
		float RandomXPosValue = UMath::RandomReturnFloat(860.0f, 1150.0f);
		float RandomYPosValue = UMath::RandomReturnFloat(360.0f, 620.0f);

		AFXBase* ExplosionEffect = GetWorld()->SpawnActor<AFXBase>("ExplosionEffect").get();
		ExplosionEffect->FXInit(ERenderingOrder::FrontFX, FAniInfo(GAniName::ExplosionEffect, GSpriteName::ExplosionEffect, 0.0416f), false);
		ExplosionEffect->SetActorLocation(float4(RandomXPosValue, -RandomYPosValue, 0.0f));
		ExplosionEffect->SetActorRotation(float4(0.0f, 0.0f, RandomAngleValue));
	}
}