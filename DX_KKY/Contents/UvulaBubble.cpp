#include "PreCompile.h"

#include "UvulaBubble.h"

AUvulaBubble::AUvulaBubble()
{
}

AUvulaBubble::~AUvulaBubble()
{
}

void AUvulaBubble::BeginPlay()
{
	Super::BeginPlay();

	AnimationInit();
	RendererInit();
	ColliderInit();
	StateInit();
}

void AUvulaBubble::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AUvulaBubble::RendererInit()
{

}

void AUvulaBubble::ColliderInit()
{

}

void AUvulaBubble::StateInit()
{

}