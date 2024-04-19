#include "PreCompile.h"

#include "CagneyCarnation.h"
#include <EngineCore/SpriteRenderer.h>

ACagneyCarnation::ACagneyCarnation()
{
}

ACagneyCarnation::~ACagneyCarnation()
{
}

void ACagneyCarnation::BeginPlay()
{
	Super::BeginPlay();

	AnimationInit();
	StateInit();
}

void ACagneyCarnation::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

