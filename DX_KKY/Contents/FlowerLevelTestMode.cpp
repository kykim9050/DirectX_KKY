#include "PreCompile.h"

#include "FlowerLevelTestMode.h"

AFlowerLevelTestMode::AFlowerLevelTestMode()
{
}

AFlowerLevelTestMode::~AFlowerLevelTestMode()
{
}

void AFlowerLevelTestMode::BeginPlay()
{
	Super::BeginPlay();
}

void AFlowerLevelTestMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AFlowerLevelTestMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}

void AFlowerLevelTestMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);
}