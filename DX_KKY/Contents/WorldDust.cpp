#include "PreCompile.h"
#include <EngineCore/SpriteRenderer.h>

#include "WorldDust.h"

AWorldDust::AWorldDust()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("WorldDustRenderer");
}

AWorldDust::~AWorldDust()
{
}

void AWorldDust::BeginPlay()
{
	Super::BeginPlay();

	Renderer->CreateAnimation("WorldDust_1", "WorldDustA", 0.1f, false);
	Renderer->CreateAnimation("WorldDust_2", "WorldDustB", 0.1f, false);
	Renderer->CreateAnimation("WorldDust_3", "WorldDustC", 0.1f, false);
	Renderer->CreateAnimation("WorldDust_4", "WorldDustD", 0.1f, false);
	Renderer->CreateAnimation("WorldDust_5", "WorldDustE", 0.1f, false);
	Renderer->CreateAnimation("WorldDust_6", "WorldDustF", 0.1f, false);

	Renderer->ChangeAnimation("WorldDust_1");
}

void AWorldDust::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}