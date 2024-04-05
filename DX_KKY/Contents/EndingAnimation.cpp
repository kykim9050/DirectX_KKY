#include "PreCompile.h"
#include "EndingAnimation.h"
#include <EngineCore/SpriteRenderer.h>

AEndingAnimation::AEndingAnimation()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
}

AEndingAnimation::~AEndingAnimation()
{
}

void AEndingAnimation::BeginPlay()
{
	Super::BeginPlay();

	SetActorScale3D(FVector(1280.0f, 720.0f, 0.0f));
	
	Renderer->SetSprite("Ending_Animation");
	Renderer->SetSamplering(ETextureSampling::LINEAR);

	Renderer->CreateAnimation("EndingPlay", "Ending_Animation", 0.03f, false);
	Renderer->ChangeAnimation("EndingPlay");
}

void AEndingAnimation::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
