#include "PreCompile.h"
#include <EngineCore/Camera.h>
#include "Player.h"

#include "TestGameMode.h"
#include "WorldDust.h"
#include "WorldGameMode.h"
#include "MapSubObject.h"
#include "WorldPlayer.h"
#include "OldFilmEffect.h"
#include "TitleAnimation.h"
#include "TitleLogo.h"

std::shared_ptr<AOldFilmEffect> ATestGameMode::OldFilm = nullptr;

ATestGameMode::ATestGameMode()
{
}

ATestGameMode::~ATestGameMode()
{
}

void ATestGameMode::BeginPlay()
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

	// 콜리젼 맵을 가져와서 ContentsValue 클래스에 정보 저장
	UContentsValue::ColMapTexture = UEngineTexture::FindRes(WorldCollisionMap->GetName());
	float4 ColMapScale = UContentsValue::ColMapTexture->GetScale();

	// OldFilm, WPlayer는 오더링 고정
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

void ATestGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void ATestGameMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}

void ATestGameMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

}