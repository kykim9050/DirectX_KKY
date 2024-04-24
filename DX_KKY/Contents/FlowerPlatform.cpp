#include "PreCompile.h"
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/Collision.h>
#include <EngineCore/SpriteRenderer.h>

#include "FlowerPlatform.h"


AFlowerPlatform::AFlowerPlatform()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("FlowerPlatformRoot");
	SetRoot(Root);

	PlatformRenderer = CreateDefaultSubObject<USpriteRenderer>("FlowerPlatformRenderer");
	PlatformRenderer->SetupAttachment(Root);

	PropellorRenderer = CreateDefaultSubObject<USpriteRenderer>("PlatformPropellorRenderer");
	PropellorRenderer->SetupAttachment(Root);

	Collider = CreateDefaultSubObject<UCollision>("FlowerPlatformCollider");
	Collider->SetupAttachment(Root);
}

AFlowerPlatform::~AFlowerPlatform()
{
}

void AFlowerPlatform::BeginPlay()
{
	Super::BeginPlay();

	AnimationInit();
	ColliderInit();
	RendererInit();
	StateInit();
}

void AFlowerPlatform::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}

void AFlowerPlatform::RendererInit()
{
	PlatformRenderer->SetAutoSize(1.0f, true);
	PlatformRenderer->SetOrder(ERenderingOrder::Object1);
	PlatformRenderer->SetPosition(float4(0.0f, 0.0f, 0.0f));

	PropellorRenderer->SetAutoSize(1.0f, true);
	PropellorRenderer->SetOrder(ERenderingOrder::Object2);
	PropellorRenderer->SetPosition(GRendererPos::FlowerPlatform_RelativePos);
}

void AFlowerPlatform::ColliderInit()
{
	Collider->SetScale(GColliderScale::FlowerPlatform_ColScale);
	Collider->SetCollisionGroup(ECollisionGroup::Platform);
	Collider->SetCollisionType(ECollisionType::Rect);
	Collider->SetPosition(GColliderPosInfo::FlowerPlatform_RelativePos);
}

void AFlowerPlatform::AnimationInit()
{
	PropellorRenderer->CreateAnimation(FlowerBossAniName::PlatformPropeller, "FlowerPlatformPropellor", 0.067f);
	PropellorRenderer->ChangeAnimation(FlowerBossAniName::PlatformPropeller);
}

void AFlowerPlatform::StateInit()
{
	State.CreateState(FlowerBossState::FlowerPlatform_Floating);
	State.CreateState(FlowerBossState::FlowerPlatform_Pressed);
	State.CreateState(FlowerBossState::FlowerPlatform_Pause);

	State.SetUpdateFunction(FlowerBossState::FlowerPlatform_Floating, std::bind(&AFlowerPlatform::Floating, this, std::placeholders::_1));
	State.SetUpdateFunction(FlowerBossState::FlowerPlatform_Pressed, std::bind(&AFlowerPlatform::Pressed, this, std::placeholders::_1));
	State.SetUpdateFunction(FlowerBossState::FlowerPlatform_Pause, [](float) {});

	State.ChangeState(FlowerBossState::FlowerPlatform_Floating);
}

void AFlowerPlatform::Floating(float _DeltaTime)
{
	float4 Pos = GetActorLocation();
	Pos.Y *= -1;

	if (Pos.Y <= GBoundaryPos::FlowerPlatform_BoundaryYPos[0])
	{
		AddActorLocation(float4::Down);
		FloatingDir = float4::Down;
	}
	else if (Pos.Y >= GBoundaryPos::FlowerPlatform_BoundaryYPos[1])
	{
		AddActorLocation(float4::Up);
		FloatingDir = float4::Up;
	}

	SetSpeedVec(FloatingDir * FloatingSpeed);

	ResultMovementUpdate(_DeltaTime);
}

void AFlowerPlatform::Pressed(float _DeltaTime)
{
	float4 Pos = GetActorLocation();
	Pos.Y *= -1;

	if (Pos.Y >= GBoundaryPos::FlowerPlatform_BoundaryYPos[1])
	{
		SetSpeedVec(float4::Zero);
		State.ChangeState(FlowerBossState::FlowerPlatform_Pause);
		return;
	}

	SetSpeedVec(float4::Down * PressedSpeed);
	ResultMovementUpdate(_DeltaTime);
}

void AFlowerPlatform::CreatePlatformAnimation(FAniInfo _info, bool _Loop)
{
	PlatformRenderer->CreateAnimation(_info.AnimationName, _info.SpriteName, _info.InterTime, _Loop);
}

void AFlowerPlatform::ChangePlatformAnimation(std::string_view _AniName)
{
	PlatformRenderer->ChangeAnimation(_AniName);
}