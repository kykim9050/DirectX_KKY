#include "PreCompile.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>

#include "CagneyCarnation.h"


ACagneyCarnation::ACagneyCarnation()
{
	HeadCollider = CreateDefaultSubObject<UCollision>("HeadCollider");
	HeadCollider->SetupAttachment(Root);
	HeadCollider->SetCollisionType(ECollisionType::Rect);

	FaceAttHighCollider = CreateDefaultSubObject<UCollision>("FaceAttHighCollider");
	FaceAttHighCollider->SetupAttachment(Root);
	FaceAttHighCollider->SetCollisionType(ECollisionType::Rect);

	FaceAttLowCollider = CreateDefaultSubObject<UCollision>("FaceAttLowCollider");
	FaceAttLowCollider->SetupAttachment(Root);
	FaceAttLowCollider->SetCollisionType(ECollisionType::Rect);
}

ACagneyCarnation::~ACagneyCarnation()
{
}

void ACagneyCarnation::BeginPlay()
{
	Super::BeginPlay();

	AnimationInit();
	StateInit();
}

void ACagneyCarnation::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

