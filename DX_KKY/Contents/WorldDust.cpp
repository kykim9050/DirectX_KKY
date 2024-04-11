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

	//Renderer->CreateAnimation("WorldDust_1", "WorldDustA", 0.1f, false);
	Renderer->CreateAnimation("WorldDust_1", "WorldDustA", 0.05f);
	Renderer->CreateAnimation("WorldDust_2", "WorldDustB", 0.05f, false);
	Renderer->CreateAnimation("WorldDust_3", "WorldDustC", 0.05f, false);
	Renderer->CreateAnimation("WorldDust_4", "WorldDustD", 0.05f, false);
	Renderer->CreateAnimation("WorldDust_5", "WorldDustE", 0.05f, false);
	Renderer->CreateAnimation("WorldDust_6", "WorldDustF", 0.05f, false);
	Renderer->SetOrder(ERenderingOrder::Dust);

	Renderer->ChangeAnimation("WorldDust_1");
	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetOrder(ERenderingOrder::Dust);
}

void AWorldDust::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}