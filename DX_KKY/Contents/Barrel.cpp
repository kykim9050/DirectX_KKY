#include "PreCompile.h"

#include "Barrel.h"

ABarrel::ABarrel()
{
}

ABarrel::~ABarrel()
{
}

void ABarrel::BeginPlay()
{
	Super::BeginPlay();

	AnimationInit();
	StateInit();
}

void ABarrel::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}

void ABarrel::RendererInit()
{

}

void ABarrel::AnimationInit()
{
	CreateAnimation();
	SetAnimationCallback();
}

void ABarrel::CreateAnimation()
{

}

void ABarrel::ColliderInit()
{

}

void ABarrel::SetAnimationCallback()
{

}

void ABarrel::StateInit()
{

}
