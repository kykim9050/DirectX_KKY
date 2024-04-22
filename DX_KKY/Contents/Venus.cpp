#include "PreCompile.h"

#include "Venus.h"

AVenus::AVenus()
{
}

AVenus::~AVenus()
{
}

void AVenus::BeginPlay()
{
	Super::BeginPlay();

	AnimationInit();
	RendererInit();
	ColliderInit();
	StateInit();
}

void AVenus::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}

void AVenus::StateInit()
{

}

void AVenus::RendererInit()
{

}

void AVenus::ColliderInit()
{

}

void AVenus::AnimationInit()
{

}