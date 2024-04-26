#include "PreCompile.h"

#include "PirateLevelMode.h"

APirateLevelMode::APirateLevelMode()
{
}

APirateLevelMode::~APirateLevelMode()
{
}

void APirateLevelMode::BeginPlay()
{
	Super::BeginPlay();
}

void APirateLevelMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void APirateLevelMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}

void APirateLevelMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);
}
