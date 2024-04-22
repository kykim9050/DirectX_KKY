﻿#include "PreCompile.h"

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

	AnimationInit();
	RendererInit();
	ColliderInit();
	StateInit();
}

void AMiniFlower::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}

void AMiniFlower::StateInit()
{
	State.CreateState(FlowerBossState::MiniFlower_Spawn);
	State.CreateState(FlowerBossState::MiniFlower_Rise);
	State.CreateState(FlowerBossState::MiniFlower_Fly);

	State.SetStartFunction(FlowerBossState::MiniFlower_Spawn, [this]()
		{
			ChangeAnimation(FlowerBossAniName::MiniFlower_Spawn);
		});
	State.SetStartFunction(FlowerBossState::MiniFlower_Rise, [this]()
		{
			ChangeAnimation(FlowerBossAniName::MiniFlower_Fly);
		});
	State.SetStartFunction(FlowerBossState::MiniFlower_Fly, [this](){});

	State.SetUpdateFunction(FlowerBossState::MiniFlower_Spawn, [this](float) {});
	State.SetUpdateFunction(FlowerBossState::MiniFlower_Rise, std::bind(&AMiniFlower::Rising, this, std::placeholders::_1));
	State.SetUpdateFunction(FlowerBossState::MiniFlower_Fly, std::bind(&AMiniFlower::Flying, this, std::placeholders::_1));

	State.ChangeState(FlowerBossState::MiniFlower_Spawn);
}

void AMiniFlower::RendererInit()
{
	SetRendererAutoSize();
	SetRendererOrder(ERenderingOrder::Monster1);
	SetRendererPivot(EPivot::BOT);
}

void AMiniFlower::ColliderInit()
{

}

void AMiniFlower::AnimationInit()
{
	CreateAnimation(FAniInfo(FlowerBossAniName::MiniFlower_Spawn , "MiniFlowerSpawn", 0.0416f), false);
	CreateAnimation(FAniInfo(FlowerBossAniName::MiniFlower_Fly, "MiniFlowerFly", 0.067f));
	CreateAnimation(FAniInfo(FlowerBossAniName::MiniFlower_Death, "MiniFlowerDeath", 0.0416f), false);
	CreateAnimation(FAniInfo(FlowerBossAniName::MiniFlower_Spit, "MiniFlowerSpit", 0.0416f), false);
	CreateRevAnimation(FAniInfo(FlowerBossAniName::MiniFlower_RevSpit, "MiniFlowerSpit", 0.0416f), false, 16, 0);

	SetRendererFrameCallback(FlowerBossAniName::MiniFlower_Spawn, 5, [this]()
		{
			State.ChangeState(FlowerBossState::MiniFlower_Rise);
		});
}

void AMiniFlower::Rising(float _DeltaTime)
{
	float4 MyPos = GetActorLocation();
	MyPos.Y *= -1;

	if (MyPos.Y <= 50.0f) {
		State.ChangeState(FlowerBossState::MiniFlower_Fly);
		return;
	}

	AddActorLocation(float4::Up * 200.0f * _DeltaTime);
}

void AMiniFlower::Flying(float _DeltaTime)
{

}