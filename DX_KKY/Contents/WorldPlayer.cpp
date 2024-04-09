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
	
	CreatePlayerAnimation();

	Renderer->ChangeAnimation("WPlayer_Idle");
}

void AWorldPlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AWorldPlayer::CreatePlayerAnimation()
{
	Renderer->CreateAnimation("WPlayer_Idle", "DiagonalDownIdle", 0.067f);
	Renderer->CreateAnimation("WPlayer_UpIdle", "UpIdle", 0.067f);
	Renderer->CreateAnimation("WPlayer_DownIdle", "DownIdle", 0.067f);
	Renderer->CreateAnimation("WPlayer_DiagonalUpIdle", "DiagonalUpIdle", 0.067f);
	Renderer->CreateAnimation("WPlayer_DiagonalDownIdle", "DiagonalDownIdle", 0.067f);
	Renderer->CreateAnimation("WPlayer_StraightIdle", "StraightIdle", 0.067f);
	Renderer->CreateAnimation("WPlayer_UpWalk", "UpWalk", 0.067f);
	Renderer->CreateAnimation("WPlayer_DownWalk", "DownWalk", 0.067f);
	Renderer->CreateAnimation("WPlayer_DiagonalUpWalk", "DiagonalUpWalk", 0.067f);
	Renderer->CreateAnimation("WPlayer_DiagonalDownWalk", "DiagonalDownWalk", 0.067f);
	Renderer->CreateAnimation("WPlayer_StraightWalk", "StraightWalk", 0.067f);
}