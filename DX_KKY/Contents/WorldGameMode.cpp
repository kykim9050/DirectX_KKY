#include "PreCompile.h"
#include <EngineCore/Camera.h>

#include "WorldGameMode.h"
#include "WorldPlayer.h"
#include "MapBase.h"
#include "FlowerLevelGate.h"
#include "PirateLevelGate.h"

AWorldGameMode::AWorldGameMode()
{
}

AWorldGameMode::~AWorldGameMode()
{
}

void AWorldGameMode::BeginPlay()
{
	Super::BeginPlay();

	WidgetInit();
	PermanentObjectCreate();
	GetWorld()->GetLastTarget()->AddEffect<UBlurEffect>();
}

void AWorldGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	ModeState.Update(_DeltaTime);
}

void AWorldGameMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);

	BGMPlayer.Off();

	DeleteObject();
}

void AWorldGameMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	BGMPlayer = UEngineSound::SoundPlay("World_bgm.wav");
	BGMPlayer.SetVolume(0.5f);
	BGMPlayer.Loop();

	WidgetStart();
	CreateObject();
	ObjectInit();
	StateInit();
}

void AWorldGameMode::WidgetInit()
{
	OldFilm = CreateWidget<UImage>(GetWorld(), "OldFilm");
	OldFilm->AddToViewPort(ERenderingOrder::OldFilmEffect);
	OldFilm->SetPosition(float4(0.0f, 0.0f, 0.0f));
	OldFilm->SetScale(GEngine->EngineWindow.GetWindowScale());
	OldFilm->CreateAnimation(GAniName::OldFilmAni, GSpriteName::OldFilm, 0.05f);

	Iris = CreateWidget<UImage>(GetWorld(), "Iris");
	Iris->AddToViewPort(ERenderingOrder::Iris);
	Iris->SetPosition(float4(0.0f, 0.0f, 0.0f));
	Iris->SetScale(GEngine->EngineWindow.GetWindowScale());
	Iris->CreateAnimation(GAniName::IrisAni, GSpriteName::Iris, 0.034f, false);
	Iris->CreateAnimation(GAniName::IrisRevAni, GSpriteName::Iris, 0.034f, false, 16, 0);
}

void AWorldGameMode::WidgetStart()
{
	OldFilm->ChangeAnimation(GAniName::OldFilmAni);
	Iris->ChangeAnimation(GAniName::IrisAni);
}

void AWorldGameMode::CreateObject()
{
	MapLayer = GetWorld()->SpawnActor<AMapBase>("MapLayer", static_cast<int>(EActorType::BackGroundSubStaticObject));
	WorldMap = GetWorld()->SpawnActor<AMapBase>("WorldMap", static_cast<int>(EActorType::Map));
	WorldCollisionMap = GetWorld()->SpawnActor<AMapBase>("WorldCollisionMap", static_cast<int>(EActorType::Map));
	FlowerLevelGate = GetWorld()->SpawnActor<AFlowerLevelGate>("FlowerLevelGate", static_cast<int>(EActorType::BackGroundSubStaticObject));
	PirateLevelGate = GetWorld()->SpawnActor<APirateLevelGate>("PirateLevelGate", static_cast<int>(EActorType::BackGroundSubStaticObject));
}

void AWorldGameMode::ObjectInit()
{
	MapLayer->SetMapFile("WorldMap_Layer.png");
	WorldMap->SetMapFile("WorldMap.png");
	WorldCollisionMap->SetMapFile("WorldMap_PixelCheck.png");
	MapLayer->SetAutoScale();
	WorldMap->SetAutoScale();
	WorldCollisionMap->SetAutoScale();

	// 콜리젼 맵을 가져와서 ContentsValue 클래스에 정보 저장
	UContentsValue::ColMapTexture = UEngineTexture::FindRes(WorldCollisionMap->GetName());
	float4 ColMapScale = UContentsValue::ColMapTexture->GetScale();

	// OldFilm, WPlayer는 오더링 고정
	MapLayer->SetOrdering(ERenderingOrder::FrontLayer2);
	WorldMap->SetOrdering(ERenderingOrder::BackLayer1);
	WorldCollisionMap->SetOrdering(ERenderingOrder::CollisionLayer);

	MapLayer->SetActorLocation(FVector{ ColMapScale.hX(), -ColMapScale.hY(), 50.0f });
	WorldMap->SetActorLocation(FVector{ ColMapScale.hX(), -ColMapScale.hY(), 200.0f });
	WorldCollisionMap->SetActorLocation(FVector{ ColMapScale.hX(), -ColMapScale.hY(), 300.0f });
	FlowerLevelGate->SetActorLocation(GActorPosValue::FlowerLevel_GatePos);
	PirateLevelGate->SetActorLocation(GActorPosValue::PirateLevel_GatePos);
}

void AWorldGameMode::DeleteObject()
{
	if (nullptr != MapLayer)
	{
		MapLayer->Destroy();
		MapLayer = nullptr;
	}

	if (nullptr != WorldMap)
	{
		WorldMap->Destroy();
		WorldMap = nullptr;
	}

	if (nullptr != WorldCollisionMap)
	{
		WorldCollisionMap->Destroy();
		WorldCollisionMap = nullptr;
	}

	if (nullptr != FlowerLevelGate)
	{
		FlowerLevelGate->Destroy();
		FlowerLevelGate = nullptr;
	}

	if (nullptr != PirateLevelGate)
	{
		PirateLevelGate->Destroy();
		PirateLevelGate = nullptr;
	}

	UContentsValue::ColMapTexture = nullptr;
}

void AWorldGameMode::PermanentObjectCreate()
{
	Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(UContentsValue::WorldMapCameraInitValue);

	WPlayer = GetWorld()->SpawnActor<AWorldPlayer>("WorldPlayer", static_cast<int>(EActorType::Player));
	WPlayer->SetActorLocation(FVector{ UContentsValue::WorldMapPlayerXInitValue, UContentsValue::WorldMapPlayerYInitValue, 100.0f });
}

void AWorldGameMode::StateInit()
{
	{
		ModeState.CreateState("Idle");
		ModeState.CreateState("FlowerLevelChange");
		ModeState.CreateState("PirateLevelChange");
	}

	{
		ModeState.SetStartFunction("FlowerLevelChange", [this]()
			{
				Iris->SetFrameCallback(GAniName::IrisRevAni, 17, [this]()
					{
						GEngine->ChangeLevel(GLevelName::FlowerLevel);
					});

				Iris->ChangeAnimation(GAniName::IrisRevAni);
			});
		ModeState.SetStartFunction("PirateLevelChange", [this]()
			{
				Iris->SetFrameCallback(GAniName::IrisRevAni, 17, [this]()
					{
						GEngine->ChangeLevel(GLevelName::PirateLevel);
					});

				Iris->ChangeAnimation(GAniName::IrisRevAni);
			});
	}

	{
		ModeState.SetUpdateFunction("Idle", std::bind(&AWorldGameMode::Idle, this, std::placeholders::_1));
		ModeState.SetUpdateFunction("FlowerLevelChange", [](float) {});
		ModeState.SetUpdateFunction("PirateLevelChange", [](float) {});
	}

	ModeState.ChangeState("Idle");
}

void AWorldGameMode::Idle(float _DeltaTime)
{
	if (true == FlowerLevelGate->GetIsGateOpen())
	{
		ModeState.ChangeState("FlowerLevelChange");
		return;
	}

	if (true == PirateLevelGate->GetIsGateOpen())
	{
		ModeState.ChangeState("PirateLevelChange");
		return;
	}
}