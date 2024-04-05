#include "PreCompile.h"
#include "TitleLogo.h"

ATitleLogo::ATitleLogo() 
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
}

ATitleLogo::~ATitleLogo() 
{
}

void ATitleLogo::BeginPlay()
{
	Super::BeginPlay();

	SetActorScale3D(FVector(960.0f, 540.0f, 100.0f));

	
	Renderer->SetSprite("Title");
	Renderer->SetSamplering(ETextureSampling::LINEAR);
	Renderer->CreateAnimation("TitlePlay", "Title", 0.08f);
	Renderer->ChangeAnimation("TitlePlay");


}

void ATitleLogo::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

