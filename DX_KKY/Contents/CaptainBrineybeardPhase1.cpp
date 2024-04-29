#include "PreCompile.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>

#include "CaptainBrineybeardPhase1.h"

ACaptainBrineybeardPhase1::ACaptainBrineybeardPhase1()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("BulletRoot");
	SetRoot(Root);

	SetHp(300);
	RendererInit();
	//ColliderInit();
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

	PirateRenderer->SetAutoSize(1.0f, true);
	PirateRenderer->SetPivot(EPivot::RIGHTBOTTOM);
	PirateRenderer->SetOrder(ERenderingOrder::Monster2);
	PirateRenderer->SetPosition(GRendererPos::Pirate_Idle_ReletivePos);

	//PirateRenderer->SetPlusColor(GColorValue::BrightColor);
}

void ACaptainBrineybeardPhase1::AnimationInit()
{
	CreateAnimation();

}