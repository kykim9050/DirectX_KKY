#include "PreCompile.h"
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/Collision.h>

#include "CaptainBrineybeardPhase2.h"
#include "UvulaBubble.h"

ACaptainBrineybeardPhase2::ACaptainBrineybeardPhase2()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");
	SetRoot(Root);

	SetHp(100);
	RendererInit();
	ColliderInit();
	SetGetHitFunction(std::bind(&ACaptainBrineybeardPhase2::AfterHitFlash, this));
}

ACaptainBrineybeardPhase2::~ACaptainBrineybeardPhase2()
{
}

void ACaptainBrineybeardPhase2::BeginPlay()
{
	Super::BeginPlay();

	AnimationInit();
	SetAnimationCallback();
	StateInit();
}

void ACaptainBrineybeardPhase2::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	DebugUpdate();
	ShipState.Update(_DeltaTime);
}

void ACaptainBrineybeardPhase2::RendererInit()
{
	ShipRenderer = CreateDefaultSubObject<USpriteRenderer>("ShipRenderer");
	ShipRenderer->SetupAttachment(Root);

	JawRenderer = CreateDefaultSubObject<USpriteRenderer>("JawRenderer");
	JawRenderer->SetupAttachment(Root);

	UvulaRenderer = CreateDefaultSubObject<USpriteRenderer>("JawRenderer");
	UvulaRenderer->SetupAttachment(Root);

	LazarRenderer = CreateDefaultSubObject<USpriteRenderer>("LazarRenderer");
	LazarRenderer->SetupAttachment(Root);



	ShipRenderer->SetAutoSize(1.2f, true);
	ShipRenderer->SetPivot(EPivot::RIGHTBOTTOM);
	ShipRenderer->SetOrder(ERenderingOrder::BossMonster);
	ShipRenderer->SetPosition(GRendererPos::Ship_Phase1_RelativePos);

	JawRenderer->SetAutoSize(1.2f, true);
	JawRenderer->SetPivot(EPivot::RIGHTBOTTOM);
	JawRenderer->SetOrder(ERenderingOrder::Object2);
	JawRenderer->SetPosition(GRendererPos::Ship_Phase1_RelativePos);
	JawRenderer->SetActive(false);

	UvulaRenderer->SetAutoSize(1.2f, true);
	UvulaRenderer->SetPivot(EPivot::RIGHTTOP);
	UvulaRenderer->SetOrder(ERenderingOrder::Monster1);
	UvulaRenderer->SetPosition(GRendererPos::Ship_Uvula_RelativePos);
	UvulaRenderer->SetPlusColor(float4(0.2f, 0.2f, 0.2f));
	UvulaRenderer->SetActive(false);

	LazarRenderer->SetAutoSize(1.2f, true);
	LazarRenderer->SetPivot(EPivot::RIGHT);
	LazarRenderer->SetOrder(ERenderingOrder::BossMonsterFrontFX1);
	LazarRenderer->SetPosition(GRendererPos::Ship_Lazar_RelativePos);
	LazarRenderer->SetPlusColor(GColorValue::BrightColor);
	LazarRenderer->SetActive(false);
}

void ACaptainBrineybeardPhase2::AnimationInit()
{
	CreateAnimation();
}

void ACaptainBrineybeardPhase2::ColliderInit()
{
	MainCollider = CreateDefaultSubObject<UCollision>("MainCollider");
	MainCollider->SetupAttachment(Root);

	LazarCollider = CreateDefaultSubObject<UCollision>("LazarCollider");
	LazarCollider->SetupAttachment(Root);



	MainCollider->SetScale(GColliderScale::PirateBoss_Phase2_ColScale);
	MainCollider->AddPosition(GColliderPosInfo::PirateBoss_Phase2_RelPos);
	MainCollider->SetCollisionGroup(ECollisionGroup::Monster);
	MainCollider->SetCollisionType(ECollisionType::Rect);
	MainCollider->SetActive(false);

	LazarCollider->SetScale(GColliderScale::PirateBoss_Lazar_ColScale);
	LazarCollider->AddPosition(GColliderPosInfo::PirateBoss_Lazar_RelPos);
	LazarCollider->SetCollisionGroup(ECollisionGroup::MonsterBullet);
	LazarCollider->SetCollisionType(ECollisionType::Rect);
	LazarCollider->SetActive(false);
}

void ACaptainBrineybeardPhase2::DebugUpdate()
{
	{
		std::string Msg = std::format("PirateBoss Phase2 Hp : {}\n", std::to_string(GetHp()));
		UEngineDebugMsgWindow::PushMsg(Msg);
	}
}

void ACaptainBrineybeardPhase2::CreateUvulaBubble()
{
	PlayShootBubbleSound();

	AUvulaBubble* Bubble = GetWorld()->SpawnActor<AUvulaBubble>("Bubble", EActorType::MonsterBullet).get();
	Bubble->SetActorLocation(GetActorLocation() + GActorPosValue::UvulaBubble_RelativePos);
}

void ACaptainBrineybeardPhase2::AfterHitFlash()
{
	ShipRenderer->SetPlusColor(GColorValue::AttackColor);
	JawRenderer->SetPlusColor(GColorValue::AttackColor);
	UvulaRenderer->SetPlusColor(GColorValue::AttackColor);

	DelayCallBack(0.05f, [this]()
		{
			ShipRenderer->SetPlusColor(GColorValue::AttackRestoreColor);
		});
	DelayCallBack(0.05f, [this]()
		{
			JawRenderer->SetPlusColor(GColorValue::AttackRestoreColor);
		});
	DelayCallBack(0.05f, [this]()
		{
			UvulaRenderer->SetPlusColor(GColorValue::AttackRestoreColor);
		});
}

void ACaptainBrineybeardPhase2::PlayShootBubbleSound()
{
	int RandomVal = UMath::RandomReturnInt(1, 4);

	UEngineSoundPlayer Sound = UEngineSound::SoundPlay("pirate_boat_uvula_shoot_0" + std::to_string(RandomVal) + ".wav");
	Sound.SetVolume(0.7f);
}