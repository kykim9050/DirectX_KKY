#include "PreCompile.h"
#include <EngineCore/Camera.h>

#include "ContentsEnumClass.h"
#include "WorldGameMode.h"
#include "WorldMap.h"
#include "MapSubObject.h"
#include "WorldPlayer.h"
#include "OldFilmEffect.h"


AWorldGameMode::AWorldGameMode()
{
}

AWorldGameMode::~AWorldGameMode()
{
}

void AWorldGameMode::BeginPlay()
{
	Super::BeginPlay();

	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(0.0f, 0.0f, -100.0f));

	std::shared_ptr<AActor> OldFilm = GetWorld()->SpawnActor<AOldFilmEffect>("OldFilmEffect", static_cast<int>(EActorType::FilmEffect));
	std::shared_ptr<AMapSubObject> MapLayer = GetWorld()->SpawnActor<AMapSubObject>("MapLayer", static_cast<int>(EActorType::BackGroundSubStaticObject));
	std::shared_ptr<AActor> WPlayer = GetWorld()->SpawnActor<AWorldPlayer>("WorldPlayer", static_cast<int>(EActorType::Player));
	std::shared_ptr<AActor>	WorldMap = GetWorld()->SpawnActor<AWorldMap>("WorldMap", static_cast<int>(EActorType::Map));


	std::shared_ptr<AWorldMap> WMap = std::dynamic_pointer_cast<AWorldMap>(WorldMap);
	
	if (nullptr == WMap)
	{
		MsgBoxAssert("올바르지 못한 업캐스팅 형식입니다.");
		return;
	}

	MapLayer->SetMapSubObject("WorldMap_Layer.png");
	MapLayer->SetMapSubObjectScale(WMap->GetMapScale());

	OldFilm->AddActorLocation(FVector{ 0.0f, 0.0f, 0.0f });
	MapLayer->AddActorLocation(FVector{ 0.0f, 0.0f, 50.0f });
	WPlayer->AddActorLocation(FVector{ 0.0f, 0.0f, 100.0f });
	WorldMap->AddActorLocation(FVector{ 0.0f, 0.0f, 200.0f });
}

void AWorldGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}