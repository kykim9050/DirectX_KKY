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

	SetActorScale3D(FVector(960.0f, 540.0f, 100.0f));


	Renderer->SetSprite("Title_Animation");
	Renderer->SetSamplering(ETextureSampling::LINEAR);
	Renderer->CreateAnimation("TitlePlay", "Title_Animation", 0.08f);
	Renderer->ChangeAnimation("TitlePlay");

}

void ATitleAnimation::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
