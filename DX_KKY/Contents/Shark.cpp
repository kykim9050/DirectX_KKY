﻿#include "PreCompile.h"
#include <EngineCore/DefaultSceneComponent.h>

#include "Shark.h"

AShark::AShark()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("BulletRoot");
	SetRoot(Root);

	RendererInit();
	ColliderInit();
}

AShark::~AShark()
{
}

void AShark::BeginPlay()
{
	Super::BeginPlay();

	AnimationInit();
	StateInit();
}

void AShark::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
	DebugUpdate();
}

void AShark::RendererInit()
{
	SharkRenderer = CreateDefaultSubObject<USpriteRenderer>("SharkRenderer");
	SharkRenderer->SetupAttachment(Root);
	SharkRenderer->SetAutoSize(1.0f, true);
	SharkRenderer->SetOrder(ERenderingOrder::SubMonster1);
	SharkRenderer->SetPivot(EPivot::LEFTBOTTOM);
	SharkRenderer->SetActive(false);
	SharkRenderer->SetPosition(GRendererPos::Shark_RelativePos);

	FinRenderer = CreateDefaultSubObject<USpriteRenderer>("FinRenderer");
	FinRenderer->SetupAttachment(Root);
	FinRenderer->SetAutoSize(1.0f, true);
	FinRenderer->SetOrder(ERenderingOrder::SharkFin);
	FinRenderer->SetActive(false);

	EffectRenderer = CreateDefaultSubObject<USpriteRenderer>("EffectRenderer");
	EffectRenderer->SetupAttachment(Root);
	EffectRenderer->SetAutoSize(1.0f, true);
	EffectRenderer->SetOrder(ERenderingOrder::FrontFX);
	EffectRenderer->SetPivot(EPivot::LEFTBOTTOM);
	EffectRenderer->SetActive(false);
	EffectRenderer->SetPosition(GRendererPos::Shark_AppearEff_RelativePos);
}

void AShark::AnimationInit()
{
	CreateAnimation();
	SetAnimationCallback();
}

void AShark::CreateAnimation()
{
	// Shark
	SharkRenderer->CreateAnimation(PirateBossAniName::Shark_Appear, "Shark_Appear.png", 0.0416f, false);
	SharkRenderer->CreateAnimation(PirateBossAniName::Shark_Chomp1, "Shark_Chomp1.png", 0.0416f, false);
	SharkRenderer->CreateAnimation(PirateBossAniName::Shark_Chomp2, "Shark_Chomp2.png", 0.0416f, false);
	SharkRenderer->CreateAnimation(PirateBossAniName::Shark_Leave, "Shark_Leave.png", 0.0416f, true);

	// ShartFin
	FinRenderer->CreateAnimation(PirateBossAniName::Shark_Before_Appear, "Shark_Fin.png", 0.0416f);

	// Effect
	EffectRenderer->CreateAnimation(PirateBossAniName::Shark_Appear_Effect, "Shark_Appear_Effect.png", 0.0416f, false);
}

void AShark::SetAnimationCallback()
{
	SharkRenderer->SetFrameCallback(PirateBossAniName::Shark_Chomp1, 10, [this]()
		{
			SetSpeedVec(float4::Zero);
			SharkRenderer->ChangeAnimation(PirateBossAniName::Shark_Chomp2);
		});

	EffectRenderer->SetFrameCallback(PirateBossAniName::Shark_Appear_Effect, 22, [this]()
		{
			EffectRenderer->SetActive(false);
		});

}

void AShark::ColliderInit()
{
	MainCollider = CreateDefaultSubObject<UCollision>("MainCollider");
	MainCollider->SetupAttachment(Root);

	MainCollider->SetScale(GColliderScale::Shark_ColScale);
	MainCollider->SetPosition(GColliderPosInfo::Shark_RelPos);
	MainCollider->SetCollisionGroup(ECollisionGroup::Monster);
	MainCollider->SetCollisionType(ECollisionType::Rect);
	MainCollider->SetActive(false);
}

void AShark::StateInit()
{
	{
		State.CreateState(PirateBossState::Shark_Appear_Intro);
		State.CreateState(PirateBossState::Shark_Appear);
		State.CreateState(PirateBossState::Shark_Chomp);
		State.CreateState(PirateBossState::Shark_Leave);
	}

	{
		State.SetStartFunction(PirateBossState::Shark_Appear_Intro, [this]()
			{
				DelayCallBack(0.5f, []()
					{
						UEngineSound::SoundPlay("pirate_shark_warning.wav");
					});

				SetSpeedVec(float4::Left * AppearIntroSpeed);
				FinRenderer->SetActive(true);
				FinRenderer->ChangeAnimation(PirateBossAniName::Shark_Before_Appear);
			});
		State.SetStartFunction(PirateBossState::Shark_Appear, [this]()
			{
				AddActorLocation(float4::Down * 170.0f);
				SetSpeedVec(float4::Right * AttackSpeed);
				SharkRenderer->SetActive(true);
				SharkRenderer->ChangeAnimation(PirateBossAniName::Shark_Appear);
				MainCollider->SetActive(true);
			});
		State.SetStartFunction(PirateBossState::Shark_Chomp, [this]()
			{
				UEngineSound::SoundPlay("pirate_shark_attack.wav");

				EffectRenderer->SetActive(true);
				EffectRenderer->AnimationReset();
				EffectRenderer->ChangeAnimation(PirateBossAniName::Shark_Appear_Effect);

				SharkRenderer->ChangeAnimation(PirateBossAniName::Shark_Chomp1);
			});
		State.SetStartFunction(PirateBossState::Shark_Leave, [this]()
			{
				LeaveSound = UEngineSound::SoundPlay("pirate_shark_exit_normal_loop.wav");
				LeaveSound.Loop();
				
				SetSpeedVec(float4::Left * LeaveSpeed);
				SharkRenderer->ChangeAnimation(PirateBossAniName::Shark_Leave);
			});
	}

	{
		State.SetUpdateFunction(PirateBossState::Shark_Appear_Intro, std::bind(&AShark::Appear_Intro, this, std::placeholders::_1));
		State.SetUpdateFunction(PirateBossState::Shark_Appear, std::bind(&AShark::Appear, this, std::placeholders::_1));
		State.SetUpdateFunction(PirateBossState::Shark_Chomp, std::bind(&AShark::Chomp, this, std::placeholders::_1));
		State.SetUpdateFunction(PirateBossState::Shark_Leave, std::bind(&AShark::Leave, this, std::placeholders::_1));
	}

	{
		State.SetEndFunction(PirateBossState::Shark_Appear_Intro, [this]()
			{
				SetSpeedVec(float4::Zero);
				FinRenderer->SetActive(false);
			});
		State.SetEndFunction(PirateBossState::Shark_Chomp, [this]()
			{
				SetSpeedVec(float4::Zero);
			});
	}

	State.ChangeState(PirateBossState::Shark_Appear_Intro);
}

void AShark::Appear_Intro(float _DeltaTime)
{
	if (GetActorLocation().X < FinMoveBoundaryValue)
	{
		State.ChangeState(PirateBossState::Shark_Appear);
		return;
	}

	ResultMovementUpdate(_DeltaTime);
}

void AShark::DebugUpdate()
{
	{
		std::string Msg = std::format("Shark Pos : {}\n", GetActorLocation().ToString());
		UEngineDebugMsgWindow::PushMsg(Msg);
	}
}

void AShark::Appear(float _DeltaTime)
{
	if (SharkRenderer->IsCurAnimationEnd())
	{
		State.ChangeState(PirateBossState::Shark_Chomp);
		return;
	}

	ResultMovementUpdate(_DeltaTime);
}

void AShark::Chomp(float _DeltaTime)
{
	if (SharkRenderer->IsCurAnimationEnd())
	{
		State.ChangeState(PirateBossState::Shark_Leave);
		return;
	}

	ResultMovementUpdate(_DeltaTime);
}

void AShark::Leave(float _DeltaTime)
{
	if (GetActorLocation().X < FinMoveBoundaryValue)
	{
		LeaveSound.Off();
		Destroy();
		return;
	}

	ResultMovementUpdate(_DeltaTime);
}