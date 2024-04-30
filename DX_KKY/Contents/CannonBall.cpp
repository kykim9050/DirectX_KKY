#include "PreCompile.h"
#include <EngineCore/SpriteRenderer.h>

#include "CannonBall.h"

ACannonBall::ACannonBall()
{
	EffectRenderer = CreateDefaultSubObject<USpriteRenderer>("EffectRenderer");
	EffectRenderer->SetupAttachment(GetRoot());

	SetVerticalDir(float4::Left);
	SetVerticalSpeed(850.0f);
}

ACannonBall::~ACannonBall()
{
}

void ACannonBall::BeginPlay()
{
	Super::BeginPlay();

	AnimationInit();
	RendererInit();
	ColliderInit();
	StateInit();
}

void ACannonBall::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void ACannonBall::RendererInit()
{
	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetOrder(ERenderingOrder::MonsterBullet);
	Renderer->SetPlusColor(GColorValue::BrightColor);
	
	EffectRenderer->SetAutoSize(1.0f, true);
	EffectRenderer->SetOrder(ERenderingOrder::MonsterBulletFX);
	EffectRenderer->SetPlusColor(GColorValue::BrightColor);
}

void ACannonBall::ColliderInit()
{
	Collision->SetScale(GColliderScale::PirateBoss_Cannon_ColScale);
	Collision->AddPosition(GColliderPosInfo::PirateBoss_CannonRelPos);
	Collision->SetCollisionGroup(ECollisionGroup::MonsterBullet);
	Collision->SetCollisionType(ECollisionType::Rect);
}

void ACannonBall::AnimationInit()
{
	Renderer->CreateAnimation(PirateBossAniName::CannonBall, "Cannonball_Idle", 0.047f);
	EffectRenderer->CreateAnimation(PirateBossAniName::CannonBall_Effect, "Cannonball_Effect", 0.047f, false);

	EffectRenderer->SetLastFrameCallback(PirateBossAniName::CannonBall_Effect, [this]()
		{
			EffectRenderer->SetActive(false);
		});
}

void ACannonBall::Fire(float _DeltaTime)
{
	if (true == BoundaryCheck(BoundaryValue, 200.0f))
	{
		Destroy();
		return;
	}

	ResultMovementUpdate(_DeltaTime);
}

void ACannonBall::StateInit()
{
	{
		State.CreateState("Init");
		State.CreateState("Fire");
	}

	{
		State.SetStartFunction("Init", [this]() {});
		State.SetStartFunction("Fire", [this]()
			{
				SetSpeedVec(GetVerticalDir() * GetVerticalSpeed());
				Renderer->ChangeAnimation(PirateBossAniName::CannonBall);

				EffectRenderer->ChangeAnimation(PirateBossAniName::CannonBall_Effect);
			});
	}

	{
		State.SetUpdateFunction("Init", [this](float)
			{
				State.ChangeState("Fire");
			});
		State.SetUpdateFunction("Fire", std::bind(&ACannonBall::Fire, this, std::placeholders::_1));
	}

	State.ChangeState("Init");
}