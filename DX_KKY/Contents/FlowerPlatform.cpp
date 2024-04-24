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
	PropellorRenderer->SetPosition(float4(5.0f, -45.0f, 0.0f));
}

void AFlowerPlatform::ColliderInit()
{
	Collider->SetScale(float4(150.0f, 16.0f, 1.0f));
	Collider->SetCollisionGroup(ECollisionGroup::Platform);
	Collider->SetCollisionType(ECollisionType::Rect);
	Collider->SetPosition(float4(0.0f, 16.0f, 0.0f));
}

void AFlowerPlatform::AnimationInit()
{
	//ShadowRenderer->CreateAnimation(FlowerBossAniName::PlatformShadow, "PlatformShadow", 0.067f);
	PropellorRenderer->CreateAnimation(FlowerBossAniName::PlatformPropeller, "FlowerPlatformPropellor", 0.067f);
	PlatformRenderer->CreateAnimation(FlowerBossAniName::FlowerPlatform, "FlowerPlatform2", 0.067f);

	//ShadowRenderer->ChangeAnimation(FlowerBossAniName::PlatformShadow);
	PropellorRenderer->ChangeAnimation(FlowerBossAniName::PlatformPropeller);
	PlatformRenderer->ChangeAnimation(FlowerBossAniName::FlowerPlatform);
}

void AFlowerPlatform::StateInit()
{
	State.CreateState("Floating");
	State.CreateState("Pressed");
	State.CreateState("Pause");

	State.SetUpdateFunction("Floating", std::bind(&AFlowerPlatform::Floating, this, std::placeholders::_1));
	State.SetUpdateFunction("Pressed", std::bind(&AFlowerPlatform::Pressed, this, std::placeholders::_1));
	State.SetUpdateFunction("Pause", [](float) {});

	State.ChangeState("Floating");
}

void AFlowerPlatform::Floating(float _DeltaTime)
{
	float4 Pos = GetActorLocation();
	Pos.Y *= -1;

	if (Pos.Y <= 400.0f)
	{
		AddActorLocation(float4::Down);
		FloatingDir = float4::Down;
	}
	else if (Pos.Y >= 450.0f)
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

	if (Pos.Y >= 450.0f)
	{
		SetSpeedVec(float4::Zero);
		State.ChangeState("Pause");
		return;
	}

	SetSpeedVec(float4::Down * 50.0f);
	ResultMovementUpdate(_DeltaTime);
}