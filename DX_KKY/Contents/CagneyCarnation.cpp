#include "PreCompile.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>

#include "CagneyCarnation.h"
#include "PlayerBullet.h"


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

	// 충돌 체크는 상태별로 업데이트 할 것
	CollisionCheck();
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
	// HeadCollider 충돌 확인
	HeadCollider->CollisionEnter(ECollisionGroup::PlayerBullet, [=](std::shared_ptr<UCollision> _Collision)
		{
			APlayerBullet* PBullet = dynamic_cast<APlayerBullet*>(_Collision->GetActor());
		
			if (nullptr == PBullet)
			{
				MsgBoxAssert("PlayerBullet으로 dynamic_cast가 불가합니다.");
				return;
			}
			
			// 본인의 체력 감소
			
			// PlayerBullet이 맞으면 Bullet Destroy
			PBullet->SetIsMonsterHit(true);

			// PlayerSSBullet에 맞으면 3번 체력 감소

		});
}

// 충돌 체크의 종류 (Head, FaceAttLow, FaceAttHigh - PlayerBullet, PlayerSSBullet 충돌 구분)

