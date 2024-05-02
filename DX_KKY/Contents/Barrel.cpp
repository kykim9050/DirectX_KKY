#include "PreCompile.h"
#include <EngineCore/DefaultSceneComponent.h>


#include "Barrel.h"

ABarrel::ABarrel()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("BulletRoot");
	SetRoot(Root);

	RendererInit();
	ColliderInit();
}

ABarrel::~ABarrel()
{
}

void ABarrel::BeginPlay()
{
	Super::BeginPlay();

	AnimationInit();
	StateInit();
}

void ABarrel::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}

void ABarrel::RendererInit()
{
	BarrelRenderer = CreateDefaultSubObject<USpriteRenderer>("BarrelRenderer");
	BarrelRenderer->SetupAttachment(Root);
	BarrelRenderer->SetAutoSize(1.0f, true);
	BarrelRenderer->SetOrder(ERenderingOrder::SubMonster1);

	DustRenderer = CreateDefaultSubObject<USpriteRenderer>("DustRenderer");
	DustRenderer->SetupAttachment(Root);
	DustRenderer->SetAutoSize(1.0f, true);
	DustRenderer->SetOrder(ERenderingOrder::FrontDust);
	DustRenderer->SetActive(false);

	EffectRenderer = CreateDefaultSubObject<USpriteRenderer>("EffectRenderer");
	EffectRenderer->SetupAttachment(Root);
	EffectRenderer->SetAutoSize(1.0f, true);
	EffectRenderer->SetOrder(ERenderingOrder::FrontFX);
	EffectRenderer->SetActive(false);
	
}

void ABarrel::AnimationInit()
{
	CreateAnimation();
	SetAnimationCallback();
}

void ABarrel::CreateAnimation()
{
	// Barrel
	BarrelRenderer->CreateAnimation(PirateBossAniName::Barrel_Normal_Idle, "Barrel_Normal_Idle.png", 0.047f, false, 0, 10);
	BarrelRenderer->CreateAnimation(PirateBossAniName::Barrel_Normal_IdleRev, "Barrel_Normal_Idle.png", 0.047f, false, 9, 1);
	BarrelRenderer->CreateAnimation(PirateBossAniName::Barrel_AttWait_Idle, "Pirate_Barrel_AttWait_Idle.png", 0.047f, false, 0, 10);
	BarrelRenderer->CreateAnimation(PirateBossAniName::Barrel_AttWait_IdleRev, "Pirate_Barrel_AttWait_Idle.png", 0.047f, false, 9, 1);
	BarrelRenderer->CreateAnimation(PirateBossAniName::Barrel_Drop_Begin, "Pirate_Barrel_Drop.png", 0.067f, false);
	BarrelRenderer->CreateAnimation(PirateBossAniName::Barrel_Dropping, "Pirate_Barrel_Drop.png", 0.067f, true, 1, 3);
	BarrelRenderer->CreateAnimation(PirateBossAniName::Barrel_Smash_Begin, "Pirate_Barrel_Smash.png", 0.067f, false);
	BarrelRenderer->CreateAnimation(PirateBossAniName::Barrel_Smashing, "Pirate_Barrel_Smash.png", 0.067f, true, 3, 4);
	BarrelRenderer->CreateAnimation(PirateBossAniName::Barrel_BackUp_Begin, "Pirate_Barrel_BackUp.png", 0.067f, false);
	BarrelRenderer->CreateAnimation(PirateBossAniName::Barrel_BackUp_Idle, "Pirate_Barrel_BackUp.png", 0.067f, true, 3, 5);

	// Dust
	DustRenderer->CreateAnimation(PirateBossAniName::Barrel_Smash_Dust, "Barrel_Smash_Dust.png", 0.047f, false);

	// Effect
	EffectRenderer->CreateAnimation(PirateBossAniName::Barrel_Smash_Effect, "Barrel_Smash_FX.png", 0.047f, false);
}


void ABarrel::ColliderInit()
{

}

void ABarrel::SetAnimationCallback()
{

	// Barrel
	BarrelRenderer->SetFrameCallback(PirateBossAniName::Barrel_Normal_Idle, 11, [this]()
		{
			BarrelRenderer->ChangeAnimation(PirateBossAniName::Barrel_Normal_IdleRev);
		});
	BarrelRenderer->SetFrameCallback(PirateBossAniName::Barrel_Normal_IdleRev, 9, [this]()
		{
			BarrelRenderer->ChangeAnimation(PirateBossAniName::Barrel_Normal_Idle);
		});
	BarrelRenderer->SetFrameCallback(PirateBossAniName::Barrel_AttWait_Idle, 11, [this]()
		{
			BarrelRenderer->ChangeAnimation(PirateBossAniName::Barrel_AttWait_IdleRev);
		});
	BarrelRenderer->SetFrameCallback(PirateBossAniName::Barrel_AttWait_IdleRev, 9, [this]()
		{
			BarrelRenderer->ChangeAnimation(PirateBossAniName::Barrel_AttWait_Idle);
		});
	BarrelRenderer->SetFrameCallback(PirateBossAniName::Barrel_Drop_Begin, 4, [this]()
		{
			BarrelRenderer->ChangeAnimation(PirateBossAniName::Barrel_Dropping);
		});
	BarrelRenderer->SetFrameCallback(PirateBossAniName::Barrel_Smash_Begin, 5, [this]()
		{
			BarrelRenderer->ChangeAnimation(PirateBossAniName::Barrel_Smashing);
		});
	BarrelRenderer->SetFrameCallback(PirateBossAniName::Barrel_BackUp_Begin, 6, [this]()
		{
			BarrelRenderer->ChangeAnimation(PirateBossAniName::Barrel_BackUp_Idle);
		});


	// Dust
	DustRenderer->SetFrameCallback(PirateBossAniName::Barrel_Smash_Dust, 23, [this]()
		{
			// 나중에 상태 끝날 때 애니메이션 초기화도 해줘야 함
			DustRenderer->SetActive(false);
		});

	// Effect
	EffectRenderer->SetFrameCallback(PirateBossAniName::Barrel_Smash_Effect, 12, [this]()
		{
			// 나중에 상태 끝날 때 애니메이션 초기화도 해줘야 함
			EffectRenderer->SetActive(false);
		});
}

void ABarrel::StateInit()
{
	{
		State.CreateState(PirateBossState::Barrel_Intro);
		State.CreateState(PirateBossState::Barrel_AttWait_Idle);
	}

	{
		State.SetStartFunction(PirateBossState::Barrel_Intro, [this]()
			{
				BarrelRenderer->ChangeAnimation(PirateBossAniName::Barrel_AttWait_Idle);
			});
		State.SetStartFunction(PirateBossState::Barrel_AttWait_Idle, [this]()
			{
				BarrelRenderer->ChangeAnimation(PirateBossAniName::Barrel_AttWait_Idle);
			});
	}

	{
		State.SetUpdateFunction(PirateBossState::Barrel_Intro, [this](float)
			{
				if (true == BarrelRenderer->IsCurAnimationEnd())
				{
					if (IntroRockTime <= IntroRockCount)
					{
						IntroRockCount = 0;
						State.ChangeState(PirateBossState::Barrel_AttWait_Idle);
						return;
					}
					++IntroRockCount;
				}
			});
		State.SetUpdateFunction(PirateBossState::Barrel_AttWait_Idle, std::bind(&ABarrel::AttWait_Idle, this, std::placeholders::_1));
	}

	State.ChangeState(PirateBossState::Barrel_Intro);
}

void ABarrel::AttWait_Idle(float _DeltaTime)
{
	float4 MyPos = GetActorLocation();

	if (MyPos.X <= PirateBossStageValue::Barrel_Moving_XBound_Min)
	{
		AddActorLocation(float4::Right);
		MoveDir = float4::Right;
	}
	else if (MyPos.X >= PirateBossStageValue::Barrel_Moving_XBound_Max)
	{
		AddActorLocation(float4::Left);
		MoveDir = float4::Left;
	}

	SetSpeedVec(MoveDir * MoveSpeed);
	ResultMovementUpdate(_DeltaTime);
}