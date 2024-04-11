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

	SetActorScale3D(FVector(1280.0f, 720.0f, 0.0f));

	Renderer->SetSprite("title_screen_background.png");
	Renderer->SetSamplering(ETextureSampling::LINEAR);
	Renderer->SetOrder(ERenderingOrder::BackLayer);
}

void ATitleLogo::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

