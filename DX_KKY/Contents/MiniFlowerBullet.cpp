#include "PreCompile.h"

#include "MiniFlowerBullet.h"

AMiniFlowerBullet::AMiniFlowerBullet()
{
}

AMiniFlowerBullet::~AMiniFlowerBullet()
{
}

void AMiniFlowerBullet::BeginPlay()
{
	Super::BeginPlay();

	StateInit();
}

void AMiniFlowerBullet::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AMiniFlowerBullet::StateInit()
{

}

void AMiniFlowerBullet::RendererInit()
{

}

void AMiniFlowerBullet::ColliderInit()
{

}

void AMiniFlowerBullet::AnimationInit()
{

}