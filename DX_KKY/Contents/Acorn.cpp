#include "PreCompile.h"

#include "Acorn.h"

AAcorn::AAcorn()
{
}

AAcorn::~AAcorn()
{
}

void AAcorn::BeginPlay()
{
	Super::BeginPlay();

	AnimationInit();
	RendererInit();
	ColliderInit();
	StateInit();
}

void AAcorn::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}

void AAcorn::StateInit()
{

}

void AAcorn::RendererInit()
{

}

void AAcorn::ColliderInit()
{

}

void AAcorn::AnimationInit()
{

}