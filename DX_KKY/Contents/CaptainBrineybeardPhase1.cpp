#include "PreCompile.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/Collision.h>

#include "CaptainBrineybeardPhase1.h"

ACaptainBrineybeardPhase1::ACaptainBrineybeardPhase1()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("BulletRoot");
	SetRoot(Root);

	SetHp(300);
	RendererInit();
	ColliderInit();
}

ACaptainBrineybeardPhase1::~ACaptainBrineybeardPhase1()
{
}

void ACaptainBrineybeardPhase1::BeginPlay()
{
	Super::BeginPlay();

	AnimationInit();
	SetAnimationCallback();
	StateInit();
}

void ACaptainBrineybeardPhase1::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	DebugUpdate();
	ShipState.Update(_DeltaTime);
	PirateState.Update(_DeltaTime);
}

void ACaptainBrineybeardPhase1::RendererInit()
{
	// Ship
	ShipRenderer = CreateDefaultSubObject<USpriteRenderer>("ShipRenderer");
	ShipRenderer->SetupAttachment(Root);

	ShipRailRenderer = CreateDefaultSubObject<USpriteRenderer>("ShipRailRenderer");
	ShipRailRenderer->SetupAttachment(Root);

	ShipMastRenderer = CreateDefaultSubObject<USpriteRenderer>("ShipMastRenderer");
	ShipMastRenderer->SetupAttachment(Root);

	ShipSailRenderer = CreateDefaultSubObject<USpriteRenderer>("ShipSailRenderer ");
	ShipSailRenderer->SetupAttachment(Root);


	ShipRenderer->SetAutoSize(1.2f, true);
	ShipRenderer->SetPivot(EPivot::RIGHTBOTTOM);
	ShipRenderer->SetOrder(ERenderingOrder::BossMonster);
	ShipRenderer->SetPosition(GRendererPos::Ship_Phase1_RelativePos);

	ShipRailRenderer->SetAutoSize(1.0f, true);
	ShipRailRenderer->SetOrder(ERenderingOrder::BossMonsterBackFX1);
	ShipRailRenderer->SetPosition(GRendererPos::ShipRail_RelativePos);

	ShipMastRenderer->SetAutoSize(1.0f, true);
	ShipMastRenderer->SetOrder(ERenderingOrder::Object3);
	ShipMastRenderer->SetPivot(EPivot::BOT);
	ShipMastRenderer->SetPosition(GRendererPos::ShipMast_RelativePos);

	ShipSailRenderer->SetAutoSize(1.0f, true);
	ShipSailRenderer->SetOrder(ERenderingOrder::Object2);
	ShipSailRenderer->SetPivot(EPivot::LEFTBOTTOM);
	ShipSailRenderer->SetPosition(GRendererPos::ShipSail_RelativePos);

	ShipRenderer->SetPlusColor(GColorValue::BrightColor);
	ShipRailRenderer->SetPlusColor(GColorValue::BrightColor);
	ShipMastRenderer->SetPlusColor(GColorValue::BrightColor);
	ShipSailRenderer->SetPlusColor(GColorValue::BrightColor);


	// Pirate
	PirateRenderer = CreateDefaultSubObject<USpriteRenderer>("PirateRenderer");
	PirateRenderer->SetupAttachment(Root);
	
	PirateTopRenderer = CreateDefaultSubObject<USpriteRenderer>("PirateTopRenderer");
	PirateTopRenderer->SetupAttachment(Root);


	PirateRenderer->SetAutoSize(1.0f, true);
	PirateRenderer->SetPivot(EPivot::RIGHTBOTTOM);
	PirateRenderer->SetOrder(ERenderingOrder::Monster2);
	PirateRenderer->SetPosition(GRendererPos::Pirate_Idle_ReletivePos);

	PirateTopRenderer->SetAutoSize(1.0f, true);
	PirateTopRenderer->SetPivot(EPivot::RIGHTBOTTOM);
	PirateTopRenderer->SetOrder(ERenderingOrder::BossMonsterFrontLayer1);
	PirateTopRenderer->SetPosition(GRendererPos::Pirate_OctoPusAtt_ReletivePos);
	PirateTopRenderer->SetActive(false);
}

void ACaptainBrineybeardPhase1::AnimationInit()
{
	CreateAnimation();
}

void ACaptainBrineybeardPhase1::ColliderInit()
{
	MainCollider = CreateDefaultSubObject<UCollision>("MainCollider");
	MainCollider->SetupAttachment(Root);

	MainCollider->SetScale(GColliderScale::PirateBoss_Phase1_ColScale);
	MainCollider->AddPosition(GColliderPosInfo::PirateBoss_Phase1_RelPos);
	MainCollider->SetCollisionGroup(ECollisionGroup::Monster);
	MainCollider->SetCollisionType(ECollisionType::Rect);
}

void ACaptainBrineybeardPhase1::DebugUpdate()
{
	{
		std::string Msg = std::format("PirateBoss Phase1 Hp : {}\n", std::to_string(GetHp()));
		UEngineDebugMsgWindow::PushMsg(Msg);
	}
}

void ACaptainBrineybeardPhase1::MoveUpAndDown(float _DeltaTime)
{
	if (0.0f == _DeltaTime)
	{
		return;
	}

	AccTime += _DeltaTime;

	AddActorLocation(float4(0.0f, 0.065f * sinf(AccTime * 1.5f), 0.0f));
}