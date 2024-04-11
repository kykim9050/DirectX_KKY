#include "PreCompile.h"
#include <EngineCore/SpriteRenderer.h>

#include "OldFilmEffect.h"



AOldFilmEffect::AOldFilmEffect()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("OldFilmEFRenderer");
}

AOldFilmEffect::~AOldFilmEffect()
{
}

void AOldFilmEffect::BeginPlay()
{
	Super::BeginPlay();

	CreateOFEFAnimation();

	Renderer->ChangeAnimation("OldFilmAni");
	Renderer->SetOrder(ERenderingOrder::OldFilmEffect);

	FVector WindowScale = GEngine->EngineWindow.GetWindowScale();

	SetActorScale3D(WindowScale);
}

void AOldFilmEffect::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AOldFilmEffect::CreateOFEFAnimation()
{
	Renderer->CreateAnimation("OldFilmAni", "OldFilmEffect", 0.05f);
}

void AOldFilmEffect::SetOrder(int _Order)
{
	Renderer->SetOrder(_Order);
}