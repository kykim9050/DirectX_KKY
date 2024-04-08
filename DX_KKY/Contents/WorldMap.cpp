#include "PreCompile.h"

#include "WorldMap.h"

AWorldMap::AWorldMap()
{
}

AWorldMap::~AWorldMap()
{
}

void AWorldMap::BeginPlay()
{
	Super::BeginPlay();

	SetMapFile("WorldMap.png");
	SetMapScale(FVector{3844.0f, 2211.0f});
}

void AWorldMap::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
