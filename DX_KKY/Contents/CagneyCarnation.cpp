#include "PreCompile.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>

#include "CagneyCarnation.h"
//#include "PlayerBullet.h"


ACagneyCarnation::ACagneyCarnation()
{
	SetHp(500);
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

	// 충돌 체크는 상태별로 업데이트 할 것
	CollisionCheck();
	DebugUpdate();
}

void ACagneyCarnation::DebugUpdate()
{
	{
		std::string Msg = std::format("FlowerBoss Hp : {}\n", std::to_string(Hp));
		UEngineDebugMsgWindow::PushMsg(Msg);
	}
}

void ACagneyCarnation::ColliderInit()
{
	HeadCollider = CreateDefaultSubObject<UCollision>("HeadCollider");
	HeadCollider->SetupAttachment(Root);
	HeadCollider->SetScale(ColliderScale::FlowerBoss_HeadColScale);
	HeadCollider->AddPosition(ColliderPosInfo::FlowerBoss_HeadColRelPos);
	HeadCollider->SetCollisionGroup(ECollisionGroup::Monster);
	HeadCollider->SetCollisionType(ECollisionType::Rect);

	FaceAttHighCollider = CreateDefaultSubObject<UCollision>("FaceAttHighCollider");
	FaceAttHighCollider->SetupAttachment(Root);
	FaceAttHighCollider->SetScale(ColliderScale::FlowerBoss_FaceAttScale);
	FaceAttHighCollider->AddPosition(ColliderPosInfo::FlowerBoss_FaceAttHighPos);
	FaceAttHighCollider->SetCollisionGroup(ECollisionGroup::Monster);
	FaceAttHighCollider->SetCollisionType(ECollisionType::Rect);
	FaceAttHighCollider->SetActive(false);

	FaceAttLowCollider = CreateDefaultSubObject<UCollision>("FaceAttLowCollider");
	FaceAttLowCollider->SetupAttachment(Root);
	FaceAttLowCollider->SetScale(ColliderScale::FlowerBoss_FaceAttScale);
	FaceAttLowCollider->AddPosition(ColliderPosInfo::FlowerBoss_FaceAttLowPos);
	FaceAttLowCollider->SetCollisionGroup(ECollisionGroup::Monster);
	FaceAttLowCollider->SetCollisionType(ECollisionType::Rect);
	FaceAttLowCollider->SetActive(false);

}

void ACagneyCarnation::CollisionCheck()
{
	//HeadCollisionCheck();

}