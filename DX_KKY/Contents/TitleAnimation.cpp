#include "PreCompile.h"
#include "TitleAnimation.h"
#include <EngineCore/SpriteRenderer.h>

ATitleAnimation::ATitleAnimation()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
}

ATitleAnimation::~ATitleAnimation()
{
}

void ATitleAnimation::BeginPlay()
{
	Super::BeginPlay();

	SetActorScale3D(FVector(1090.0f, 620.0f, 0.0f));
	SetActorLocation(FVector(0.0f, -(360.0f - 310.0f), 0.0f));

	Renderer->SetSprite("Title_Animation");
	Renderer->SetSamplering(ETextureSampling::LINEAR);
	Renderer->CreateAnimation("TitlePlay", "Title_Animation", 0.085f);
	Renderer->ChangeAnimation("TitlePlay");
}

void ATitleAnimation::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
