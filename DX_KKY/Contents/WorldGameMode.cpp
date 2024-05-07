#include "PreCompile.h"
#include <EngineCore/Camera.h>

#include "WorldGameMode.h"
#include "WorldPlayer.h"
#include "MapBase.h"
#include "FlowerLevelGate.h"

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
}

void AWorldGameMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);

	DeleteObject();
}

void AWorldGameMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	WidgetStart();
	CreateObject();
	ObjectInit();
}

void AWorldGameMode::WidgetInit()
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
	MapLayer->SetOrdering(ERenderingOrder::FrontLayer);
	WorldMap->SetOrdering(ERenderingOrder::BackLayer1);
	WorldCollisionMap->SetOrdering(ERenderingOrder::CollisionLayer);

	MapLayer->SetActorLocation(FVector{ ColMapScale.hX(), -ColMapScale.hY(), 50.0f });
	WorldMap->SetActorLocation(FVector{ ColMapScale.hX(), -ColMapScale.hY(), 200.0f });
	WorldCollisionMap->SetActorLocation(FVector{ ColMapScale.hX(), -ColMapScale.hY(), 300.0f });
	FlowerLevelGate->SetActorLocation(GActorPosValue::FlowerLevel_GatePos);

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

	UContentsValue::ColMapTexture = nullptr;
}

void AWorldGameMode::PermanentObjectCreate()
{
	Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(UContentsValue::WorldMapCameraInitValue);

	WPlayer = GetWorld()->SpawnActor<AWorldPlayer>("WorldPlayer", static_cast<int>(EActorType::Player));
	WPlayer->SetActorLocation(FVector{ UContentsValue::WorldMapPlayerXInitValue, UContentsValue::WorldMapPlayerYInitValue, 100.0f });
}