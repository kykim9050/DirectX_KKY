#include "PreCompile.h"

#include "ContentsEnumClass.h"
#include "WorldGameMode.h"
#include "WorldMap.h"
#include "MapSubObject.h"

AWorldGameMode::AWorldGameMode()
{
}

AWorldGameMode::~AWorldGameMode()
{
}

void AWorldGameMode::BeginPlay()
{
	Super::BeginPlay();

	std::shared_ptr<AMapSubObject> MapLayer = GetWorld()->SpawnActor<AMapSubObject>("MapLayer", static_cast<int>(EActorType::BackGroundSubStaticObject));
	std::shared_ptr<AActor>	WorldMap = GetWorld()->SpawnActor<AWorldMap>("WorldMap", static_cast<int>(EActorType::Map));

	std::shared_ptr<AWorldMap> WMap = std::dynamic_pointer_cast<AWorldMap>(WorldMap);
	
	if (nullptr == WMap)
	{
		MsgBoxAssert("올바르지 못한 업캐스팅 형식입니다.");
		return;
	}

	MapLayer->SetMapSubObject("WorldMap_Layer.png");
	MapLayer->SetMapSubObjectScale(WMap->GetMapScale());

	MapLayer->AddActorLocation(FVector{ 0.0f, 0.0f, 50.0f });
	WorldMap->AddActorLocation(FVector{ 0.0f, 0.0f, 200.0f });
}

void AWorldGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}