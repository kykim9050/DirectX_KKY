#include "PreCompile.h"
#include <EngineCore/Camera.h>
#include <EngineCore/StateManager.h>
#include <EngineCore/EngineEditorGUI.h>

#include "PirateLevelMode.h"
#include "PirateLevelMap.h"
#include "CaptainBrineybeardPhase1.h"
#include "CaptainBrineybeardPhase2.h"
#include "TimeScaleControlUnit.h"
#include "Message.h"
#include "Barrel.h"
#include "Shark.h"
#include "CallSeaDogs.h"
#include "PirateLevelDebugWindow.h"

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

	DebugWindow->Off();
	BGMPlayer.Off();
}

void APirateLevelMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	ObjectInit();
	StateInit();

	OldFilm->ChangeAnimation(GAniName::OldFilmAni);
	Iris->ChangeAnimation(GAniName::IrisAni);

	DebugWindow->SetSharkAppearFunction(std::bind(&APirateLevelMode::ObjectCreate_Shark, this));
	DebugWindow->SetSeaDogAppearFunction(std::bind(&APirateLevelMode::ObjectCreate_SeaDog, this));
	DebugWindow->On();

	BGMPlayer = UEngineSound::SoundPlay("PirateLevel_bgm.mp3");
	BGMPlayer.SetVolume(0.75f);
	BGMPlayer.Loop();
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
	Iris->CreateAnimation(GAniName::IrisRevAni, GSpriteName::Iris, 0.034f, false, 16, 0);
	Iris->SetPosition(float4(0.0f, 0.0f, 0.0f));
	Iris->SetScale(GEngine->EngineWindow.GetWindowScale());
}

void APirateLevelMode::CreateObject()
{
	Camera = GetWorld()->GetMainCamera();

	DebugWindow = UEngineEditorGUI::CreateEditorWindow<UPirateLevelDebugWindow>("PirateLevelDebugWindow");
	DebugWindow->Off();
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
				{
					int Random = UMath::GetInst().RandomReturnInt(1, 2);
					UEngineSound::SoundPlay("level_announcer_0001_" + std::to_string(Random) + ".wav");
					UEngineSound::SoundPlay("level_bell_intro.wav");

					DelayCallBack(2.5f, [=]
						{
							UEngineSound::SoundPlay("level_announcer_0002_" + std::to_string(Random) + ".wav");
						});
				}

				// 페이즈1 보스 생성
				DelayCallBack(0.8f, [this]()
					{
						ScreenMsg->SetStageStartMsg();
					});

				Phase1_Boss = GetWorld()->SpawnActor<ACaptainBrineybeardPhase1>("Phase1_Boss", EActorType::BossMonster);
				Phase1_Boss->SetActorLocation(GActorPosValue::Phase1_Boss_Pos);

				Barrel = GetWorld()->SpawnActor<ABarrel>("Barrel", EActorType::Monster);
				Barrel->SetActorLocation(GActorPosValue::Barrel_Init_Pos);
			});
		ModeState.SetStartFunction("Phase2", [this]()
			{
				// 페이즈2 보스 생성
				Phase2_Boss = GetWorld()->SpawnActor<ACaptainBrineybeardPhase2>("Phase2_Boss ", EActorType::BossMonster);
				Phase2_Boss->SetActorLocation(GActorPosValue::Phase1_Boss_Pos);
			});
		ModeState.SetStartFunction("GameEnd", [this]()
			{
				BGMPlayer.Off();

				ScreenMsg->SetStageEndMsg();

				Iris->SetFrameCallback(GAniName::IrisRevAni, 17, [this]()
					{
						GEngine->ChangeLevel(GLevelName::EndingLevel);
					});

				// 레벨 전환 기능
				DelayCallBack(3.5f, [this]()
					{
						Iris->ChangeAnimation(GAniName::IrisRevAni);
					});
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

void APirateLevelMode::ObjectCreate_Shark()
{
	AShark* Shark = GetWorld()->SpawnActor<AShark>("Shark", EActorType::Monster).get();
	Shark->SetActorLocation(GActorPosValue::Shark_Init_Pos);
}

void APirateLevelMode::ObjectCreate_SeaDog()
{
	std::shared_ptr<ACallSeaDogs> SeaDogs = GetWorld()->SpawnActor<ACallSeaDogs>("SeaDogs", EActorType::Monster);
}