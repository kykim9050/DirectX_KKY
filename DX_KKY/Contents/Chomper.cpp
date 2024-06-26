﻿#include "PreCompile.h"

#include "Chomper.h"


AChomper::AChomper()
{
	SetHp(2);
}

AChomper::~AChomper()
{
}

void AChomper::BeginPlay()
{
	Super::BeginPlay();

	AnimationInit();
	RendererInit();
	ColliderInit();
	StateInit();
}

void AChomper::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}

void AChomper::StateInit()
{
	State.CreateState(FlowerBossState::Chomp);
	State.CreateState(FlowerBossState::Chomp_Death);

	State.SetStartFunction(FlowerBossState::Chomp, [this]()
		{
			UEngineSoundPlayer Sound = UEngineSound::SoundPlay("sfx_flower_plant_chomper.wav");
			Sound.SetVolume(0.5f);

			ChangeAnimation(FlowerBossAniName::Chomper_Chomp);
		});
	State.SetStartFunction(FlowerBossState::Chomp_Death, [this]()
		{
			GetCollider()->SetActive(false);
			ChangeAnimation(FlowerBossAniName::Chomper_Death);
		});

	State.SetUpdateFunction(FlowerBossState::Chomp, std::bind(&AChomper::Chomp, this, std::placeholders::_1));
	State.SetUpdateFunction(FlowerBossState::Chomp_Death, [this](float) {});

	State.ChangeState(FlowerBossState::Chomp);
}

void AChomper::RendererInit()
{
	SetRendererAutoSize();
	SetRendererOrder(ERenderingOrder::Monster1);
	SetRendererPivot(EPivot::BOT);
}

void AChomper::ColliderInit()
{
	SetColScale(GColliderScale::Chomper_ColScale);
	SetColGroup(ECollisionGroup::Monster);
	SetColType(ECollisionType::Rect);
}

void AChomper::AnimationInit()
{
	CreateAnimation(FAniInfo(FlowerBossAniName::Chomper_Chomp, GSpriteName::Chomper_Chomp, 0.0416f));
	CreateAnimation(FAniInfo(FlowerBossAniName::Chomper_Death, GSpriteName::Chomper_Death, 0.0416f), false);
	
	SetRendererFrameCallback(FlowerBossAniName::Chomper_Death, 15, [this]()
		{
			Destroy();
		});
}

void AChomper::Chomp(float _DeltaTime)
{
	if (0 >= GetHp())
	{
		State.ChangeState(FlowerBossState::Chomp_Death);
		return;
	}
}