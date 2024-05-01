﻿#include "PreCompile.h"

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
	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetOrder(ERenderingOrder::MonsterBullet);
	Renderer->SetPlusColor(GColorValue::BrightColor);
}

void AUvulaBubble::AnimationInit()
{
	Renderer->CreateAnimation(PirateBossAniName::Ship_Phase2_Bubble_Spawn, "Uvula_Bubble_Appear", 0.047f, false);
	Renderer->CreateAnimation(PirateBossAniName::Ship_Phase2_Bubble_Idle, "Uvula_Bubble_Idle", 0.047f);
	Renderer->CreateAnimation(PirateBossAniName::Ship_Phase2_Bubble_Pop, "Uvula_Bubble_Pops", 0.047f, false);

	Renderer->SetFrameCallback(PirateBossAniName::Ship_Phase2_Bubble_Spawn, 3, [this]()
		{
			SetVerticalDir(float4::Left);
			SetVerticalSpeed(500.0f);
			SetSpeedVec(GetVerticalDir() * GetVerticalSpeed());

			Renderer->ChangeAnimation(PirateBossAniName::Ship_Phase2_Bubble_Idle);
		});
}

void AUvulaBubble::ColliderInit()
{

}

void AUvulaBubble::StateInit()
{
	{
		State.CreateState(GStateName::Bullet_Init);
		State.CreateState(GStateName::Bullet_Fire);
	}

	{
		State.SetStartFunction(GStateName::Bullet_Init, []() {});
		State.SetStartFunction(GStateName::Bullet_Fire, [this]()
			{
				Renderer->ChangeAnimation(PirateBossAniName::Ship_Phase2_Bubble_Spawn);
			});
	}

	{
		State.SetUpdateFunction(GStateName::Bullet_Init, [this](float)
			{
				State.ChangeState(GStateName::Bullet_Fire);
				return;
			});
		State.SetUpdateFunction(GStateName::Bullet_Fire, std::bind(&AUvulaBubble::Fire, this, std::placeholders::_1));
	}

	State.ChangeState(GStateName::Bullet_Init);
}

void AUvulaBubble::Fire(float _DeltaTime)
{
	if (true == BoundaryCheck(BoundaryValue, 200.0f))
	{
		Destroy();
		return;
	}

	ResultMovementUpdate(_DeltaTime);
}