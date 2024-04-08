#include "PreCompile.h"

#include "ContentsEnumClass.h"
#include "WorldGameMode.h"
#include "WorldMap.h"


AWorldGameMode::AWorldGameMode()
{
}

AWorldGameMode::~AWorldGameMode()
{
}

void AWorldGameMode::BeginPlay()
{
	Super::BeginPlay();

	std::shared_ptr<AActor>	WorldMap = GetWorld()->SpawnActor<AWorldMap>("WorldMap", static_cast<int>(EActorType::Map));
	WorldMap->AddActorLocation(FVector{ 0.0f, 0.0f, 200.0f });
}

void AWorldGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}