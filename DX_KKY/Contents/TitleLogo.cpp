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

	SetActorScale3D(FVector(700.0f, 300.0f, 100.0f));

	//Renderer->SetSamplering(ETextureSampling::LINEAR);
	Renderer->SetSprite("Title");
	Renderer->CreateAnimation("TitlePlay", "Title", 0.08f);
	Renderer->ChangeAnimation("TitlePlay");


}

void ATitleLogo::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

