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

	ShadowRenderer = CreateDefaultSubObject<USpriteRenderer>("PlatformShadowRenderer");
	ShadowRenderer->SetupAttachment(Root);
	
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
}

void AFlowerPlatform::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AFlowerPlatform::RendererInit()
{

}

void AFlowerPlatform::ColliderInit()
{

}

void AFlowerPlatform::AnimationInit()
{

}