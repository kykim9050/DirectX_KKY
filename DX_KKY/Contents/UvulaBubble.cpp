#include "PreCompile.h"

#include "UvulaBubble.h"

AUvulaBubble::AUvulaBubble()
{
	SetVerticalDir(float4::Left);
	SetVerticalSpeed(300.0f);
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
	Renderer->AddPosition(ComponentPivotDist);
}

void AUvulaBubble::AnimationInit()
{
	Renderer->CreateAnimation(PirateBossAniName::Ship_Phase2_Bubble_Spawn, "Uvula_Bubble_Appear", 0.047f, false);
	Renderer->CreateAnimation(PirateBossAniName::Ship_Phase2_Bubble_Idle, "Uvula_Bubble_Idle", 0.047f);
	Renderer->CreateAnimation(PirateBossAniName::Ship_Phase2_Bubble_Pop, "Uvula_Bubble_Pops", 0.047f, false);

	Renderer->SetFrameCallback(PirateBossAniName::Ship_Phase2_Bubble_Spawn, 3, [this]()
		{
			Renderer->ChangeAnimation(PirateBossAniName::Ship_Phase2_Bubble_Idle);
		});
}

void AUvulaBubble::ColliderInit()
{
	Collision->SetScale(GColliderScale::PirateBoss_Bubble_ColScale);
	Collision->SetCollisionGroup(ECollisionGroup::MonsterBullet);
	Collision->SetCollisionType(ECollisionType::Rect);
	Collision->AddPosition(ComponentPivotDist);
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
				SetSpeedVec(GetVerticalDir() * GetVerticalSpeed());

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
	if (true == BoundaryCheck(BoundaryValue, 300.0f))
	{
		Destroy();
		return;
	}

	AccTime += _DeltaTime;

	SetActorRotation(float4(0.0f, 0.0f, -AccTime * RotationSpeed));
	Renderer->SetRotationDeg(float4(0.0f, 0.0f, AccTime * RotationSpeed));
	Collision->SetRotationDeg(float4(0.0f, 0.0f, AccTime * RotationSpeed));
	ResultMovementUpdate(_DeltaTime);
}