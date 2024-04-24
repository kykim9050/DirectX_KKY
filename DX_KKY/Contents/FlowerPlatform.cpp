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

	//ShadowRenderer = CreateDefaultSubObject<USpriteRenderer>("PlatformShadowRenderer");
	//ShadowRenderer->SetupAttachment(Root);
	//
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
	RendererInit();
	ColliderInit();
}

void AFlowerPlatform::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AFlowerPlatform::RendererInit()
{
	//ShadowRenderer->SetAutoSize(1.0f, true);
	//ShadowRenderer->SetOrder(ERenderingOrder::Object2);
	//ShadowRenderer->SetPosition(float4(0.0f, -200.0f, 0.0f));

	PlatformRenderer->SetAutoSize(1.0f, true);
	PlatformRenderer->SetOrder(ERenderingOrder::Object1);
	PlatformRenderer->SetPosition(float4(0.0f, 0.0f, 0.0f));

	PropellorRenderer->SetAutoSize(1.0f, true);
	PropellorRenderer->SetOrder(ERenderingOrder::Object2);
	PropellorRenderer->SetPosition(float4(5.0f, -45.0f, 0.0f));

}

void AFlowerPlatform::ColliderInit()
{

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