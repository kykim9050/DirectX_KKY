﻿#include "PreCompile.h"

#include "Venus.h"

AVenus::AVenus()
{
	SetHp(2);
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
	State.CreateState(FlowerBossState::Venus_Spawn);
	State.CreateState(FlowerBossState::Venus_Flying);
	State.CreateState(FlowerBossState::Venus_Death);

	State.SetStartFunction(FlowerBossState::Venus_Spawn, [this]()
		{
			UEngineSoundPlayer Sound = UEngineSound::SoundPlay("sfx_flower_venus_grow_end.wav");
			Sound.SetVolume(0.3f);

			ChangeAnimation(FlowerBossAniName::Venus_Spawn);
		});
	State.SetStartFunction(FlowerBossState::Venus_Flying, [this]()
		{
			BoundaryValue = GEngine->EngineWindow.GetWindowScale();

			float4 Direction = (UContentsFunction::GetStagePlayer()->GetActorLocation() - GetActorLocation()).Normalize2DReturn();
			Velocity = Direction * Speed;
			float Theta = UMath::DirectionToDeg(Direction);
			SetActorRotation(float4(0.0f, 0.0f, Theta + 180.0f));

			ChangeAnimation(FlowerBossAniName::Venus_Loop);
		});
	State.SetStartFunction(FlowerBossState::Venus_Death, [this]()
		{
			GetCollider()->SetActive(false);
			ChangeAnimation(FlowerBossAniName::Venus_Death);
		});

	State.SetUpdateFunction(FlowerBossState::Venus_Spawn, [this](float) {});
	State.SetUpdateFunction(FlowerBossState::Venus_Flying, std::bind(&AVenus::Flying, this, std::placeholders::_1));
	State.SetUpdateFunction(FlowerBossState::Venus_Death, [this](float) {});

	State.ChangeState(FlowerBossState::Venus_Spawn);
}

void AVenus::RendererInit()
{
	SetRendererAutoSize();
	SetRendererOrder(ERenderingOrder::Monster1);
	//SetRendererPivot(EPivot::BOT);
}

void AVenus::ColliderInit()
{
	SetColScale(GColliderScale::Venus_ColScale);
	SetColGroup(ECollisionGroup::Monster);
	SetColType(ECollisionType::RotRect);
}

void AVenus::AnimationInit()
{
	CreateAnimation(FAniInfo(FlowerBossAniName::Venus_Spawn, GSpriteName::Venus_Spawn, 0.0416f), false);
	CreateAnimation(FAniInfo(FlowerBossAniName::Venus_Loop, GSpriteName::Venus_Loop, 0.067f));
	CreateAnimation(FAniInfo(FlowerBossAniName::Venus_Death, GSpriteName::Venus_Death, 0.0416f), false);

	SetRendererFrameCallback(FlowerBossAniName::Venus_Spawn, 6, [this]()
		{
			State.ChangeState(FlowerBossState::Venus_Flying);
		});
	SetRendererFrameCallback(FlowerBossAniName::Venus_Death, 10, [this]()
		{
			Destroy();
		});
}

void AVenus::Flying(float _DeltaTime)
{
	if (0 >= GetHp() || true == BoundaryCheck(BoundaryValue))
	{
		State.ChangeState(FlowerBossState::Venus_Death);
		return;
	}

	AddActorLocation(Velocity * _DeltaTime);
}

