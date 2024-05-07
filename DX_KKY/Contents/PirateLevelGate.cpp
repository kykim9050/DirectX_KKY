#include "PreCompile.h"
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/Collision.h>

#include "PirateLevelGate.h"

APirateLevelGate::APirateLevelGate()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");
	SetRoot(Root);

	ShipRenderer = CreateDefaultSubObject<USpriteRenderer>("ShipRenderer");
	ShipRenderer->SetupAttachment(Root);

	RipplesRenderer = CreateDefaultSubObject<USpriteRenderer>("RipplesRenderer");
	RipplesRenderer->SetupAttachment(Root);

	Collider = CreateDefaultSubObject<UCollision>("Collider");
	Collider->SetupAttachment(Root);
}

APirateLevelGate::~APirateLevelGate()
{
}

void APirateLevelGate::BeginPlay()
{
	Super::BeginPlay();

	RendererInit();
	ColliderInit();
}

void APirateLevelGate::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void APirateLevelGate::RendererInit()
{
	ShipRenderer->SetAutoSize(0.75f, true);
	ShipRenderer->SetOrder(ERenderingOrder::FrontLayer1);
	ShipRenderer->CreateAnimation(GAniName::PirateLevel_GateAni, "ShootinNLootin_Ship.png", 0.1f);
	ShipRenderer->ChangeAnimation(GAniName::PirateLevel_GateAni);

	RipplesRenderer->SetAutoSize(0.75f, true);
	RipplesRenderer->SetOrder(ERenderingOrder::Object1);
	RipplesRenderer->SetPosition(GRendererPos::ShipRipples_RelativePos);
	RipplesRenderer->CreateAnimation(GAniName::PirateLevel_SubAni, "ShootinNLootin_Ripples.png", 0.1f);
	RipplesRenderer->ChangeAnimation(GAniName::PirateLevel_SubAni);
}

void APirateLevelGate::ColliderInit()
{
	Collider->SetScale(GColliderScale::WorldModeShip_ColScale);
	Collider->SetCollisionGroup(ECollisionGroup::Gate);
	Collider->SetCollisionType(ECollisionType::Rect);
}