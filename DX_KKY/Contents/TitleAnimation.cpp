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
	Renderer->CreateAnimation("TitlePlay", "Title_Animation", 0.045f);
	Renderer->SetSamplering(ETextureSampling::LINEAR);
	Renderer->ChangeAnimation("TitlePlay");
	//Renderer->SetPlusColor(FVector(0.2f, 0.2f, 0.2f, 1.0f));

}

void ATitleAnimation::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
