﻿#include "PreCompile.h"

#include "Boomerang.h"

ABoomerang::ABoomerang()
{
}

ABoomerang::~ABoomerang()
{
}

void ABoomerang::BeginPlay()
{
	Super::BeginPlay();

	AnimationInit();
	RendererInit();
	ColliderInit();
	StateInit();
}

void ABoomerang::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}

void ABoomerang::StateInit()
{
	State.CreateState(FlowerBossState::Boomerang_Init);
	State.CreateState(FlowerBossState::Boomerang_Spawn);
	State.CreateState(FlowerBossState::Boomerang_Throw);
	State.CreateState(FlowerBossState::Boomerang_ComeBack);

	State.SetStartFunction(FlowerBossState::Boomerang_Init, []() {});
	State.SetStartFunction(FlowerBossState::Boomerang_Spawn, [this]()
		{
			Sound = UEngineSound::SoundPlay("sfx_flower_boomerang_projectile.wav");
			Sound.Loop();

			Renderer->ChangeAnimation(FlowerBossAniName::Boomerang_Rotate);
		});
	State.SetStartFunction(FlowerBossState::Boomerang_Throw, [this]()
		{
			SetSpeedVec(ThrowingDir * ThrowingSpeed);
		});
	State.SetStartFunction(FlowerBossState::Boomerang_ComeBack, [this]()
		{
			AddActorLocation(float4(0.0f, -250.0f, 0.0f));
			ThrowingDir = float4::Right;
			SetSpeedVec(ThrowingDir * ThrowingSpeed);
			DelayCallBack(2.5f, [this]
				{
					Sound.Off();
					Destroy();
				});
		});

	State.SetUpdateFunction(FlowerBossState::Boomerang_Init, [this](float)
		{
			BoundaryValue = GEngine->EngineWindow.GetWindowScale();
			State.ChangeState(FlowerBossState::Boomerang_Spawn);
			return;
		});
	State.SetUpdateFunction(FlowerBossState::Boomerang_Spawn, [](float) {});
	State.SetUpdateFunction(FlowerBossState::Boomerang_Throw, std::bind(&ABoomerang::Throwing, this, std::placeholders::_1));
	State.SetUpdateFunction(FlowerBossState::Boomerang_ComeBack, std::bind(&ABoomerang::ComeBack, this, std::placeholders::_1));

	State.ChangeState(FlowerBossState::Boomerang_Init);
}

void ABoomerang::RendererInit()
{
	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetOrder(ERenderingOrder::MonsterBullet);
}

void ABoomerang::ColliderInit()
{
	Collision->SetScale(GColliderScale::Boomerang_ColScale);
	Collision->SetCollisionGroup(ECollisionGroup::MonsterBullet);
	Collision->SetCollisionType(ECollisionType::Rect);
	Collision->SetPosition(float4(0.0f, 0.0f, 0.0f));
}

void ABoomerang::AnimationInit()
{
	Renderer->CreateAnimation(FlowerBossAniName::Boomerang_Rotate, GSpriteName::Boomerang_Rotate, 0.0416f);
}

void ABoomerang::Throwing(float _DeltaTime)
{
	if (true == BoundaryCheck(BoundaryValue, 400.0f))
	{
		State.ChangeState(FlowerBossState::Boomerang_ComeBack);
		return;
	}

	ResultMovementUpdate(_DeltaTime);
}

void ABoomerang::ComeBack(float _DeltaTime)
{
	ResultMovementUpdate(_DeltaTime);
}