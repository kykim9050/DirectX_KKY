#include "PreCompile.h"
#include <EngineCore/SpriteRenderer.h>

#include "WorldPlayer.h"

AWorldPlayer::AWorldPlayer()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("PlayerRenderer");
	InputOn();
}

AWorldPlayer::~AWorldPlayer()
{
}

void AWorldPlayer::BeginPlay()
{
	Super::BeginPlay();

	SetActorScale3D(FVector(60.0f, 86.0f, 0.0f));

	Renderer->CreateAnimation("WPlayer_Idle", "DiagonalDownIdle", 0.067f);
	Renderer->ChangeAnimation("WPlayer_Idle");
}

void AWorldPlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}