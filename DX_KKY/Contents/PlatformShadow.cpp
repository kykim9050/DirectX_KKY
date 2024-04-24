#include "PreCompile.h"

#include "PlatformShadow.h"

APlatformShadow::APlatformShadow()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	SetRoot(Renderer);

	Renderer->CreateAnimation(FlowerBossAniName::PlatformShadow, "PlatformShadow", 0.067f);
	Renderer->ChangeAnimation(FlowerBossAniName::PlatformShadow);

	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetOrder(ERenderingOrder::Object2);
}

APlatformShadow::~APlatformShadow()
{
}

void APlatformShadow::BeginPlay()
{
	Super::BeginPlay();
}

void APlatformShadow::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}