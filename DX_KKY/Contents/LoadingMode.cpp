#include "PreCompile.h"

#include "LoadingMode.h"

ALoadingMode::ALoadingMode()
{
}

ALoadingMode::~ALoadingMode()
{
}

void ALoadingMode::BeginPlay()
{
	Super::BeginPlay();
}

void ALoadingMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void ALoadingMode::LevelEnd(ULevel* _NextLevel)
{

}

void ALoadingMode::LevelStart(ULevel* _PrevLevel)
{

}

