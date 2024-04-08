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

	SetActorScale3D(FVector{1280.0f, 720.0f});
}

void AOldFilmEffect::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AOldFilmEffect::CreateOFEFAnimation()
{
	Renderer->CreateAnimation("OldFilmAni", "OldFilmEffect", 0.05f);
}