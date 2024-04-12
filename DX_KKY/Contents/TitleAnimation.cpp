#include "PreCompile.h"
#include "TitleAnimation.h"
#include <EngineCore/SpriteRenderer.h>

ATitleAnimation::ATitleAnimation()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	SetRoot(Renderer);

	Renderer->SetPivot(EPivot::BOT);
}

ATitleAnimation::~ATitleAnimation()
{
}

void ATitleAnimation::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetSprite("Title_Animation");
	Renderer->CreateAnimation("TitlePlay", "Title_Animation", 0.045f);
	Renderer->SetSamplering(ETextureSampling::LINEAR);

	Renderer->SetAutoSize(1.0f, true);

	SetActorLocation(FVector(0.0f, -GEngine->EngineWindow.GetWindowScale().hY(), 0.0f));

	Renderer->ChangeAnimation("TitlePlay");
	Renderer->SetOrder(ERenderingOrder::Animation);
}

void ATitleAnimation::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
