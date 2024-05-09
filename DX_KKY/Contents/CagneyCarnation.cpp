#include "PreCompile.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>


#include "CagneyCarnation.h"
#include "Acorn.h"
#include "FXUnit.h"
#include "Boomerang.h"
#include "Vine.h"
#include "FlowerLevelMode.h"
#include "FlowerLevelDebugWindow.h"

#include "PlayerBullet.h"

ACagneyCarnation::ACagneyCarnation()
{
	SetHp(300);
	ColliderInit();
	RendererInit();
	SetGetHitFunction(std::bind(&ACagneyCarnation::AfterHitFlash, this));
}

ACagneyCarnation::~ACagneyCarnation()
{
}

void ACagneyCarnation::BeginPlay()
{
	Super::BeginPlay();

	// functional로 패턴을 마음대로 바꿀 수 있는 디버깅관련 함수 bind
	AFlowerLevelMode::DebugWindow->SetFunction(std::bind(&ACagneyCarnation::Dbg_ChangePattern, this, std::placeholders::_1));

	CreateVine();
	AnimationInit();
	StateInit();
}

void ACagneyCarnation::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

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
	HeadCollider->SetPosition(GColliderPosInfo::FlowerBoss_HeadColRelPos);
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

	BottomIvyCollider = CreateDefaultSubObject<UCollision>("BottomIvyCollider");
	BottomIvyCollider->SetupAttachment(Root);
	BottomIvyCollider->SetScale(GColliderScale::BottomIvy_ColScale);
	BottomIvyCollider->AddPosition(GColliderPosInfo::FlowerBoss_BottomIvy_RelativePos);
	BottomIvyCollider->SetCollisionGroup(ECollisionGroup::Trap);
	BottomIvyCollider->SetCollisionType(ECollisionType::Rect);
	BottomIvyCollider->SetActive(false);
}

void ACagneyCarnation::CreateAcorn()
{
	for (int i = 0; i < AcornNum; i++)
	{
		AAcorn* NewAcorn = GetWorld()->SpawnActor<AAcorn>("Acorn").get();

		NewAcorn->SetActorLocation(GColliderPosInfo::AcornInitPos[i]);
		NewAcorn->DelayCallBack(0.5f + 0.5f * i, [NewAcorn]()
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

void ACagneyCarnation::CreateBoomerang()
{
	ABoomerang* NewBoomerang = GetWorld()->SpawnActor<ABoomerang>("CreateEffect").get();
	NewBoomerang->SetActorLocation(GRendererPos::FlowerBoss_BoomarangInitPos);
	NewBoomerang->DelayCallBack(0.5f, [NewBoomerang]()
		{
			NewBoomerang->Throw();
		});
}

void ACagneyCarnation::CreateBottomIvy()
{
	BottomIvyCollider->SetActive(true);
	BottomIvyRenderer->ChangeAnimation(FlowerBossAniName::BottomIvy_Spawn);
}

void ACagneyCarnation::RendererInit()
{
	BottomIvyRenderer = CreateDefaultSubObject<USpriteRenderer>("BottomIvyRenderer");
	BottomIvyRenderer->SetupAttachment(Root);
	BottomIvyRenderer->SetAutoSize(1.0f, true);
	BottomIvyRenderer->SetOrder(ERenderingOrder::BossMonsterObject1);
	BottomIvyRenderer->SetPivot(EPivot::RIGHTBOTTOM);
	BottomIvyRenderer->SetPosition(GRendererPos::FlowerBoss_BottomIvy_RelativePos);
}

void ACagneyCarnation::CreateVine()
{
	for (int i = 0; i < VineNum; i++)
	{
		AVine* NewVine = GetWorld()->SpawnActor<AVine>("Vine").get();
		NewVine->SetActorLocation(FlowerBossStageValue::AttackableVinePos[i]);

		Vines.push_back(NewVine);
	}
}

void ACagneyCarnation::VineGrowUp()
{
	int ExceptVineNum = UMath::RandomReturnInt(0, 2);

	for (int i = 0; i < VineNum; i++)
	{
		if (ExceptVineNum == i)
		{
			continue;
		}

		float GrowUpRandomValue = UMath::RandomReturnFloat(1.0f, 2.0f);

		DelayCallBack(GrowUpRandomValue, [this, i]()
			{
				Vines[i]->GrowUp();
			});
	}
}

void ACagneyCarnation::AfterHitFlash()
{
	Renderer->SetPlusColor(GColorValue::AttackColor);

	DelayCallBack(0.05f, [this]()
		{
			Renderer->SetPlusColor(GColorValue::AttackRestoreColor);
		});
}

void ACagneyCarnation::Dbg_ChangePattern(int _PatternNum)
{
	if (-1 != PatternNum)
	{
		return;
	}

	PatternNum = _PatternNum;
}