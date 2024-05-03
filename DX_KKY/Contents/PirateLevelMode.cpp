#include "PreCompile.h"
#include <EngineCore/Camera.h>
#include <EngineCore/StateManager.h>

#include "PirateLevelMode.h"
#include "PirateLevelMap.h"
#include "CaptainBrineybeardPhase1.h"
#include "CaptainBrineybeardPhase2.h"
#include "TimeScaleControlUnit.h"
#include "Message.h"
#include "Barrel.h"
#include "Shark.h"

APirateLevelMode::APirateLevelMode()
{
}

APirateLevelMode::~APirateLevelMode()
{
}

void APirateLevelMode::BeginPlay()
{
	Super::BeginPlay();

	WidgetInit();
	CreateObject();
	GetWorld()->GetLastTarget()->AddEffect<UBlurEffect>();
}

void APirateLevelMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	ModeState.Update(_DeltaTime);
}

void APirateLevelMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);

	DeleteObject();
}

void APirateLevelMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	ObjectInit();
	StateInit();

	OldFilm->ChangeAnimation(GAniName::OldFilmAni);
	Iris->ChangeAnimation(GAniName::IrisAni);
}

void APirateLevelMode::WidgetInit()
{
	OldFilm = CreateWidget<UImage>(GetWorld(), "OldFilm");
	OldFilm->AddToViewPort(ERenderingOrder::OldFilmEffect);
	OldFilm->CreateAnimation(GAniName::OldFilmAni, GSpriteName::OldFilm, 0.05f);
	OldFilm->SetPosition(float4(0.0f, 0.0f, 0.0f));
	OldFilm->SetScale(GEngine->EngineWindow.GetWindowScale());

	Iris = CreateWidget<UImage>(GetWorld(), "Iris");
	Iris->AddToViewPort(ERenderingOrder::Iris);
	Iris->CreateAnimation(GAniName::IrisAni, GSpriteName::Iris, 0.034f, false);
	Iris->SetPosition(float4(0.0f, 0.0f, 0.0f));
	Iris->SetScale(GEngine->EngineWindow.GetWindowScale());
}

void APirateLevelMode::CreateObject()
{
	Camera = GetWorld()->GetMainCamera();
}

void APirateLevelMode::ObjectInit()
{
	Camera->SetActorLocation(UContentsValue::ContentsCameraInitPos);

	Map = GetWorld()->SpawnActor<APirateLevelMap>("Map", EActorType::Map);
	Map->SetActorLocation(float4(640.0f, -360.0f, 0.0f));

	Player = GetWorld()->SpawnActor<APlayer>("Player", EActorType::Player);
	Player->SetActorLocation(GActorPosValue::PL_Player_Init_Pos);

	TimeControlUnit = GetWorld()->SpawnActor<UTimeScaleControlUnit>("TimeControlUnit", EActorType::TimeScaleController);

	ScreenMsg = GetWorld()->SpawnActor<AMessage>("ScreenMsg", EActorType::ScreenMsg);
}

void APirateLevelMode::DeleteObject()
{
	if (nullptr != Player)
	{
		Player->Destroy();
		Player = nullptr;
	}

	if (nullptr != Phase1_Boss)
	{
		Phase1_Boss->Destroy();
		Phase1_Boss = nullptr;
	}

	if (nullptr != Phase2_Boss)
	{
		Phase2_Boss->Destroy();
		Phase2_Boss = nullptr;
	}

	if (nullptr != Map)
	{
		Map->ReleaseColMapTexInfo();
		Map->Destroy();
		Map = nullptr;
	}

	if (nullptr != TimeControlUnit)
	{
		TimeControlUnit->Destroy();
		TimeControlUnit = nullptr;
	}

	if (nullptr != ScreenMsg)
	{
		ScreenMsg->Destroy();
		ScreenMsg = nullptr;
	}

	if (nullptr != Barrel)
	{
		Barrel->Destroy();
		Barrel = nullptr;
	}
}

void APirateLevelMode::StateInit()
{
	{
		ModeState.CreateState("Phase1");
		ModeState.CreateState("Phase2");
		ModeState.CreateState("GameEnd");
	}

	{
		ModeState.SetStartFunction("Phase1", [this]()
			{
				// 페이즈1 보스 생성
				DelayCallBack(0.8f, [this]()
					{
						ScreenMsg->SetStageStartMsg();
					});

				Phase1_Boss = GetWorld()->SpawnActor<ACaptainBrineybeardPhase1>("Phase1_Boss", EActorType::BossMonster);
				Phase1_Boss->SetActorLocation(GActorPosValue::Phase1_Boss_Pos);

				Barrel = GetWorld()->SpawnActor<ABarrel>("Barrel", EActorType::Monster);
				Barrel->SetActorLocation(GActorPosValue::Barrel_Init_Pos);

				// Debug용 오브젝트 생성 기능
				ObjectCreate_DebugMode();
			});
		ModeState.SetStartFunction("Phase2", [this]()
			{
				// 페이즈2 보스 생성
				Phase2_Boss = GetWorld()->SpawnActor<ACaptainBrineybeardPhase2>("Phase2_Boss ", EActorType::BossMonster);
				Phase2_Boss->SetActorLocation(GActorPosValue::Phase1_Boss_Pos);
			});
		ModeState.SetStartFunction("GameEnd", [this]()
			{
				ScreenMsg->SetStageEndMsg();
			});
	}
	
	{
		ModeState.SetUpdateFunction("Phase1", std::bind(&APirateLevelMode::Phase1, this, std::placeholders::_1));
		ModeState.SetUpdateFunction("Phase2", std::bind(&APirateLevelMode::Phase2, this, std::placeholders::_1));
		ModeState.SetUpdateFunction("GameEnd", [](float) {});
	}

	{
		ModeState.SetEndFunction("Phase1", [this]()
			{
				if (nullptr != Phase1_Boss)
				{
					Phase1_Boss->Destroy();
					Phase1_Boss = nullptr;
				}
			});
	}

	ModeState.ChangeState("Phase1");
}

void APirateLevelMode::Phase1(float _DeltaTime)
{
	if (true == Phase1_Boss->GetIsPhaseEnd())
	{
		ModeState.ChangeState("Phase2");
		return;
	}
}

void APirateLevelMode::Phase2(float _DeltaTime)
{
	if (true == Phase2_Boss->GetIsPhaseEnd())
	{
		ModeState.ChangeState("GameEnd");
		return;
	}
}


void APirateLevelMode::ObjectCreate_DebugMode()
{
	AShark* Shark = GetWorld()->SpawnActor<AShark>("Shark", EActorType::Monster).get();
	Shark->SetActorLocation(float4(640.0f, -320.0f, 0.0f));
}