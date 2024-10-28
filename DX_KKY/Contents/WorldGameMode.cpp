#include "PreCompile.h"
#include <EngineCore/Camera.h>

#include "WorldGameMode.h"
#include "WorldPlayer.h"
#include "MapBase.h"
#include "OldFilmEffect.h"


std::shared_ptr<AOldFilmEffect> AWorldGameMode::OldFilm = nullptr;

AWorldGameMode::AWorldGameMode()
{
}

AWorldGameMode::~AWorldGameMode()
{
}

void AWorldGameMode::BeginPlay()
{
	Super::BeginPlay();

	Camera = GetWorld()->GetMainCamera();
	OldFilm = GetWorld()->SpawnActor<AOldFilmEffect>("OldFilmEffect", static_cast<int>(EActorType::FilmEffect));
	std::shared_ptr<AWorldPlayer> WPlayer = GetWorld()->SpawnActor<AWorldPlayer>("WorldPlayer", static_cast<int>(EActorType::Player));
	std::shared_ptr<AMapBase> MapLayer = GetWorld()->SpawnActor<AMapBase>("MapLayer", static_cast<int>(EActorType::BackGroundSubStaticObject));
	std::shared_ptr<AMapBase> WorldMap = GetWorld()->SpawnActor<AMapBase>("WorldMap", static_cast<int>(EActorType::Map));
	std::shared_ptr<AMapBase> WorldCollisionMap = GetWorld()->SpawnActor<AMapBase>("WorldCollisionMap", static_cast<int>(EActorType::Map));

	MapLayer->SetMapFile("WorldMap_Layer.png");
	WorldMap->SetMapFile("WorldMap.png");
	WorldCollisionMap->SetMapFile("WorldMap_PixelCheck.png");
	MapLayer->SetAutoScale();
	WorldMap->SetAutoScale();
	WorldCollisionMap->SetAutoScale();

	// �ݸ��� ���� �����ͼ� ContentsValue Ŭ������ ���� ����
	UContentsValue::ColMapTexture = UEngineTexture::FindRes(WorldCollisionMap->GetName());
	float4 ColMapScale = UContentsValue::ColMapTexture->GetScale();

	// OldFilm, WPlayer�� ������ ����
	MapLayer->SetOrdering(ERenderingOrder::FrontLayer);
	WorldMap->SetOrdering(ERenderingOrder::BackLayer);
	WorldCollisionMap->SetOrdering(ERenderingOrder::CollisionLayer);

	Camera->SetActorLocation(UContentsValue::WorldMapCameraInitValue);
	OldFilm->AddActorLocation(FVector{ UContentsValue::WorldMapPlayerXInitValue, UContentsValue::WorldMapPlayerYInitValue, 0.0f });
	WPlayer->AddActorLocation(FVector{ UContentsValue::WorldMapPlayerXInitValue, UContentsValue::WorldMapPlayerYInitValue, 100.0f });
	MapLayer->AddActorLocation(FVector{ ColMapScale.hX(), -ColMapScale.hY(), 50.0f });
	WorldMap->AddActorLocation(FVector{ ColMapScale.hX(), -ColMapScale.hY(), 200.0f });
	WorldCollisionMap->AddActorLocation(FVector{ ColMapScale.hX(), -ColMapScale.hY(), 300.0f });

}

void AWorldGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AWorldGameMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}

void AWorldGameMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

}