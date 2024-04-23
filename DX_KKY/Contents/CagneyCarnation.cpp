#include "PreCompile.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>

#include "CagneyCarnation.h"
#include "Acorn.h"
#include "FXUnit.h"


ACagneyCarnation::ACagneyCarnation()
{
	SetHp(300);
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
		std::string Msg = std::format("FlowerBoss Hp : {}\n", std::to_string(GetHp()));
		UEngineDebugMsgWindow::PushMsg(Msg);
	}
}

void ACagneyCarnation::ColliderInit()
{
	HeadCollider = CreateDefaultSubObject<UCollision>("HeadCollider");
	HeadCollider->SetupAttachment(Root);
	HeadCollider->SetScale(GColliderScale::FlowerBoss_HeadColScale);
	HeadCollider->AddPosition(GColliderPosInfo::FlowerBoss_HeadColRelPos);
	HeadCollider->SetCollisionGroup(ECollisionGroup::Monster);
	HeadCollider->SetCollisionType(ECollisionType::Rect);

	FaceAttHighCollider = CreateDefaultSubObject<UCollision>("FaceAttHighCollider");
	FaceAttHighCollider->SetupAttachment(Root);
	FaceAttHighCollider->SetScale(GColliderScale::FlowerBoss_FaceAttScale);
	FaceAttHighCollider->AddPosition(GColliderPosInfo::FlowerBoss_FaceAttHighPos);
	FaceAttHighCollider->SetCollisionGroup(ECollisionGroup::Monster);
	FaceAttHighCollider->SetCollisionType(ECollisionType::Rect);
	FaceAttHighCollider->SetActive(false);

	FaceAttLowCollider = CreateDefaultSubObject<UCollision>("FaceAttLowCollider");
	FaceAttLowCollider->SetupAttachment(Root);
	FaceAttLowCollider->SetScale(GColliderScale::FlowerBoss_FaceAttScale);
	FaceAttLowCollider->AddPosition(GColliderPosInfo::FlowerBoss_FaceAttLowPos);
	FaceAttLowCollider->SetCollisionGroup(ECollisionGroup::Monster);
	FaceAttLowCollider->SetCollisionType(ECollisionType::Rect);
	FaceAttLowCollider->SetActive(false);

}

void ACagneyCarnation::CollisionCheck()
{

}

void ACagneyCarnation::CreateAcorn()
{
	for (int i = 0; i < AcornNum; i++)
	{
		AAcorn* NewAcorn = GetWorld()->SpawnActor<AAcorn>("Acorn").get();

		//Acorns.push_back(NewAcorn);
		NewAcorn->SetActorLocation(GColliderPosInfo::AcornInitPos[i]);
		NewAcorn->DelayCallBack(1.0f + 0.5f * i, [NewAcorn]()
			{
				NewAcorn->Shoot();
			});
	}
}

void ACagneyCarnation::CreateObjectSpawnEffect()
{
	// 부메랑이던지 도토리 미사일이던지 전부다 적용되는 효과
	AFXUnit* CreateEffect = GetWorld()->SpawnActor<AFXUnit>("CreateEffect").get();
	CreateEffect->CreateAnimation(FAniInfo(FlowerBossAniName::Flower_CreateObject_Effect, GSpriteName::Flower_CreateObject_Effect, 0.033f), false);
	CreateEffect->SetRendererFrameCallback(FlowerBossAniName::Flower_CreateObject_Effect, 15, [CreateEffect]()
		{
			CreateEffect->Destroy();
		});
	CreateEffect->SetActorLocation(GColliderPosInfo::AcornInitPos[2]);
	CreateEffect->SetRendererAutoSize();
	CreateEffect->SetRendererOrder(ERenderingOrder::MonsterBulletFX);
	CreateEffect->ChangeAnimation(FlowerBossAniName::Flower_CreateObject_Effect);
}