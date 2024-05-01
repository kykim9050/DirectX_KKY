#include "PreCompile.h"
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/Collision.h>

#include "CaptainBrineybeardPhase2.h"

ACaptainBrineybeardPhase2::ACaptainBrineybeardPhase2()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("BulletRoot");
	SetRoot(Root);

	SetHp(150);
	RendererInit();
	ColliderInit();
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
	// RightTop 만들기
	UvulaRenderer->SetPivot(EPivot::RIGHT);
	UvulaRenderer->SetOrder(ERenderingOrder::Monster1);
	// 위치 수정
	UvulaRenderer->SetPosition(float4(-400.0f, 300.0f, 0.0f));
	UvulaRenderer->SetActive(false);

	LazarRenderer->SetAutoSize(1.2f, true);
	LazarRenderer->SetPivot(EPivot::RIGHT);
	LazarRenderer->SetOrder(ERenderingOrder::BossMonsterFrontFX1);
	LazarRenderer->SetPosition(GRendererPos::Ship_Lazar_ReletivePos);
	LazarRenderer->SetPlusColor(GColorValue::BrightColor);
	LazarRenderer->SetActive(false);
}

void ACaptainBrineybeardPhase2::AnimationInit()
{
	CreateAnimation();
}

void ACaptainBrineybeardPhase2::ColliderInit()
{
	LazarCollider = CreateDefaultSubObject<UCollision>("LazarCollider");
	LazarCollider->SetupAttachment(Root);

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