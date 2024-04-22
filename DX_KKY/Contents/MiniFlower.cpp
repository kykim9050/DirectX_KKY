#include "PreCompile.h"

#include "MiniFlower.h"

AMiniFlower::AMiniFlower()
{
}

AMiniFlower::~AMiniFlower()
{
}

void AMiniFlower::BeginPlay()
{
	Super::BeginPlay();
}

void AMiniFlower::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AMiniFlower::StateInit()
{

}

void AMiniFlower::RendererInit()
{

}

void AMiniFlower::ColliderInit()
{

}

void AMiniFlower::AnimationInit()
{
	//CreateAnimation("MiniFlowerSpawn", "MiniFlowerSpawn", 0.0416f, false);
	//CreateAnimation("MiniFlowerSpawn", "MiniFlowerSpawn", 0.0416f, false);
	//renderer_->CreateAnimationFolder("MiniFlowerFly", 0.067f);
	//renderer_->CreateAnimationFolder("MiniFlowerDeath", 0.0416f, false);
	//renderer_->CreateAnimationFolder("MiniFlowerSpit", 0.0416f, false);
	//renderer_->CreateAnimationFolderReverse("MiniFlowerSpitReverse", "MiniFlowerSpit", 0.0416f, false);
}