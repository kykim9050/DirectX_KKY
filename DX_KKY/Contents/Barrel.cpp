#include "PreCompile.h"
#include <EngineCore/DefaultSceneComponent.h>


#include "Barrel.h"

ABarrel::ABarrel()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("BulletRoot");
	SetRoot(Root);

	RendererInit();
	ColliderInit();

	SetGravityAccVec(float4::Down * 1500.0f);
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
	DebugUpdate();
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
	BarrelRenderer->CreateAnimation(PirateBossAniName::Barrel_Normal_Idle_Begin, "Barrel_Normal_Idle.png", 0.047f, false, 5, 0);
	BarrelRenderer->CreateAnimation(PirateBossAniName::Barrel_Normal_IdleRev, "Barrel_Normal_Idle.png", 0.047f, false, 9, 1);
	BarrelRenderer->CreateAnimation(PirateBossAniName::Barrel_AttWait_Idle, "Pirate_Barrel_AttWait_Idle.png", 0.047f, false, 0, 10);
	BarrelRenderer->CreateAnimation(PirateBossAniName::Barrel_AttWait_IdleRev, "Pirate_Barrel_AttWait_Idle.png", 0.047f, false, 9, 1);
	BarrelRenderer->CreateAnimation(PirateBossAniName::Barrel_Drop_Begin, "Pirate_Barrel_Drop.png", 0.057f, false);
	BarrelRenderer->CreateAnimation(PirateBossAniName::Barrel_Dropping, "Pirate_Barrel_Drop.png", 0.057f, true, 1, 3);
	BarrelRenderer->CreateAnimation(PirateBossAniName::Barrel_Smash_Begin, "Pirate_Barrel_Smash.png", 0.057f, false);
	BarrelRenderer->CreateAnimation(PirateBossAniName::Barrel_Smashing, "Pirate_Barrel_Smash.png", 0.057f, true, 3, 4);
	BarrelRenderer->CreateAnimation(PirateBossAniName::Barrel_Smash_End, "Pirate_Barrel_Smash.png", 0.057f, false, 3, 0);
	BarrelRenderer->CreateAnimation(PirateBossAniName::Barrel_BackUp_Begin, "Pirate_Barrel_BackUp.png", 0.057f, false);
	BarrelRenderer->CreateAnimation(PirateBossAniName::Barrel_BackUp_Idle, "Pirate_Barrel_BackUp.png", 0.057f, true, 3, 5);


	// Dust
	DustRenderer->CreateAnimation(PirateBossAniName::Barrel_Smash_Dust, "Barrel_Smash_Dust.png", 0.047f, false);

	// Effect
	EffectRenderer->CreateAnimation(PirateBossAniName::Barrel_Smash_Effect, "Barrel_Smash_FX.png", 0.047f, false);
}


void ABarrel::ColliderInit()
{
	MainCollider = CreateDefaultSubObject<UCollision>("MainCollider");
	MainCollider->SetupAttachment(Root);

	MainCollider->SetScale(GColliderScale::Barrel_ColScale);
	MainCollider->SetCollisionGroup(ECollisionGroup::Trap);
	MainCollider->SetCollisionType(ECollisionType::Rect);
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
	BarrelRenderer->SetFrameCallback(PirateBossAniName::Barrel_Smash_End, 4, [this]()
		{
			State.ChangeState(PirateBossState::Barrel_BackUp);
		});
	BarrelRenderer->SetFrameCallback(PirateBossAniName::Barrel_Normal_Idle_Begin, 6, [this]()
		{
			BarrelRenderer->ChangeAnimation(PirateBossAniName::Barrel_Normal_Idle);
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
		State.CreateState(PirateBossState::Barrel_Drop);
		State.CreateState(PirateBossState::Barrel_Smash);
		State.CreateState(PirateBossState::Barrel_BackUp);
		State.CreateState(PirateBossState::Barrel_Normal_Idle);
	}

	{
		State.SetStartFunction(PirateBossState::Barrel_Intro, [this]()
			{
				BarrelRenderer->ChangeAnimation(PirateBossAniName::Barrel_AttWait_Idle);
				MainCollider->SetPosition(GColliderPosInfo::Barrel_Idle_RelPos);
				BarrelRenderer->SetPosition(GRendererPos::Barrel_AttWait_RelativePos);
			});
		State.SetStartFunction(PirateBossState::Barrel_AttWait_Idle, [this]()
			{
				BarrelRenderer->ChangeAnimation(PirateBossAniName::Barrel_AttWait_Idle);
				MainCollider->SetPosition(GColliderPosInfo::Barrel_Idle_RelPos);
				BarrelRenderer->SetPosition(GRendererPos::Barrel_AttWait_RelativePos);
			});
		State.SetStartFunction(PirateBossState::Barrel_Drop, [this]()
			{
				BarrelRenderer->ChangeAnimation(PirateBossAniName::Barrel_Drop_Begin);
				MainCollider->SetPosition(GColliderPosInfo::Barrel_Drop_RelPos);
				BarrelRenderer->SetPosition(GRendererPos::Barrel_Drop_RelativePos);
				SetSpeedVec(float4::Zero);
			});
		State.SetStartFunction(PirateBossState::Barrel_Smash, [this]()
			{
				BarrelRenderer->ChangeAnimation(PirateBossAniName::Barrel_Smash_Begin);
				BarrelRenderer->SetPosition(GRendererPos::Barrel_Smash_RelativePos);
				SetGravityVec(float4::Zero);
			});
		State.SetStartFunction(PirateBossState::Barrel_BackUp, [this]()
			{
				BarrelRenderer->ChangeAnimation(PirateBossAniName::Barrel_BackUp_Begin);
				SetJumpVec(float4::Up * BackUpSpeed);
			});
		State.SetStartFunction(PirateBossState::Barrel_Normal_Idle, [this]()
			{
				BarrelRenderer->ChangeAnimation(PirateBossAniName::Barrel_Normal_Idle_Begin);
				BarrelRenderer->SetPosition(GRendererPos::Barrel_NormalIdle_RelativePos);
				SetJumpVec(float4::Zero);
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
		State.SetUpdateFunction(PirateBossState::Barrel_Drop, std::bind(&ABarrel::Drop, this, std::placeholders::_1));
		State.SetUpdateFunction(PirateBossState::Barrel_Smash, [this](float)
			{
				if (true == BarrelRenderer->IsCurAnimationEnd())
				{
					if (SmashTime <= SmashCount)
					{
						SmashCount = 0;
						BarrelRenderer->ChangeAnimation(PirateBossAniName::Barrel_Smash_End);
						return;
					}
					++SmashCount;
				}
			});
		State.SetUpdateFunction(PirateBossState::Barrel_BackUp, std::bind(&ABarrel::BackUp, this, std::placeholders::_1));
		State.SetUpdateFunction(PirateBossState::Barrel_Normal_Idle, std::bind(&ABarrel::Normal_Idle, this, std::placeholders::_1));
	}

	State.ChangeState(PirateBossState::Barrel_Intro);
}

bool ABarrel::PlayerNearCheck(float4 _MyPos)
{
	float4 PlayerPos = UContentsFunction::GetStagePlayer()->GetActorLocation();
	float4 MyPos = _MyPos;

	float XValue = abs(PlayerPos.X - MyPos.X);

	if (AttackRange >= XValue)
	{
		return true;
	}

	return false;
}

bool ABarrel::DropEndLineCheck(float4 _MyPos)
{
	float4 MyPos = _MyPos;
	MyPos.Y *= -1;

	if (MyPos.Y >= DropEndLine)
	{
		return true;
	}

	return false;
}

void ABarrel::AttWait_Idle(float _DeltaTime)
{
	float4 MyPos = GetActorLocation();

	if (true == PlayerNearCheck(MyPos))
	{
		State.ChangeState(PirateBossState::Barrel_Drop);
		return;
	}

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

void ABarrel::Drop(float _DeltaTime)
{
	if (true == DropEndLineCheck(GetActorLocation()))
	{
		State.ChangeState(PirateBossState::Barrel_Smash);
		return;
	}

	CalGravityVec(_DeltaTime);
	ResultMovementUpdate(_DeltaTime);
}

void ABarrel::BackUp(float _DeltaTime)
{
	if (GetActorLocation().Y >= GActorPosValue::Barrel_Init_Pos.Y)
	{
		State.ChangeState(PirateBossState::Barrel_Normal_Idle);
		return;
	}

	ResultMovementUpdate(_DeltaTime);
}

void ABarrel::Normal_Idle(float _DeltaTime)
{
	if (true == BarrelRenderer->IsCurAnimationEnd())
	{
		if (NorIdleTime <= NorIdleCount)
		{
			NorIdleCount = 0;
			State.ChangeState(PirateBossState::Barrel_AttWait_Idle);
			return;
		}
		++NorIdleCount;
	}

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

void ABarrel::DebugUpdate()
{
	{
		std::string Msg = std::format("Barrel Pos : {}\n", GetActorLocation().ToString());
		UEngineDebugMsgWindow::PushMsg(Msg);
	}
}

