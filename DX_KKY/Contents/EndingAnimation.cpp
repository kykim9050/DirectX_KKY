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

	SetActorScale3D(GEngine->EngineWindow.GetWindowScale());
	
	Renderer->SetSprite("Ending_Animation");
	Renderer->SetSamplering(ETextureSampling::LINEAR);

	Renderer->CreateAnimation("EndingPlay", "Ending_Animation", 0.03f, false);
	Renderer->ChangeAnimation("EndingPlay");

	Renderer->SetOrder(EEndingRenderingOrder::Animation);
}

void AEndingAnimation::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
