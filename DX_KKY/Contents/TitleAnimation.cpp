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

	SetActorScale3D(FVector(1280.0f, 720.0f, 100.0f));

	Renderer->SetSprite("title_screen_background.png");
	Renderer->SetSamplering(ETextureSampling::LINEAR);
}

void ATitleAnimation::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
