#include "PreCompile.h"

#include "ContentsCamera.h"

UContentsCamera::UContentsCamera()
{
}

UContentsCamera::~UContentsCamera()
{
}

void UContentsCamera::BeginPlay()
{
	Super::BeginPlay();
}

void UContentsCamera::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void UContentsCamera::End()
{
	Super::End();
}

void UContentsCamera::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);
}

void UContentsCamera::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}