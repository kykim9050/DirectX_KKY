#include "PreCompile.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>

#include "CagneyCarnation.h"


ACagneyCarnation::ACagneyCarnation()
{
	ColliderInit();
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

void ACagneyCarnation::ColliderInit()
{
	HeadCollider = CreateDefaultSubObject<UCollision>("HeadCollider");
	HeadCollider->SetupAttachment(Root);
	HeadCollider->SetScale(ColliderScale::FlowerBoss_HeadColScale);
	HeadCollider->AddPosition(ColliderPosInfo::FlowerBoss_HeadColRelPos);
	HeadCollider->SetCollisionGroup(ECollisionOrder::Monster);
	HeadCollider->SetCollisionType(ECollisionType::Rect);

	FaceAttHighCollider = CreateDefaultSubObject<UCollision>("FaceAttHighCollider");
	FaceAttHighCollider->SetupAttachment(Root);
	FaceAttHighCollider->SetScale(ColliderScale::FlowerBoss_FaceAttScale);
	FaceAttHighCollider->AddPosition(ColliderPosInfo::FlowerBoss_FaceAttHighPos);
	FaceAttHighCollider->SetCollisionGroup(ECollisionOrder::Monster);
	FaceAttHighCollider->SetCollisionType(ECollisionType::Rect);
	FaceAttHighCollider->SetActive(false);

	FaceAttLowCollider = CreateDefaultSubObject<UCollision>("FaceAttLowCollider");
	FaceAttLowCollider->SetupAttachment(Root);
	FaceAttLowCollider->SetScale(ColliderScale::FlowerBoss_FaceAttScale);
	FaceAttLowCollider->AddPosition(ColliderPosInfo::FlowerBoss_FaceAttLowPos);
	FaceAttLowCollider->SetCollisionGroup(ECollisionOrder::Monster);
	FaceAttLowCollider->SetCollisionType(ECollisionType::Rect);
	FaceAttLowCollider->SetActive(false);

}