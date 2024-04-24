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
}

void AFlowerPlatform::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
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
	Collider->SetPosition(float4(0.0f, 24.0f, 0.0f));
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