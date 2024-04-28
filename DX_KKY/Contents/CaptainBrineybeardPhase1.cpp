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
	//StateInit();
}

void ACaptainBrineybeardPhase1::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void ACaptainBrineybeardPhase1::RendererInit()
{
	// Ship
	ShipRenderer = CreateDefaultSubObject<USpriteRenderer>("ShipRenderer");
	ShipRenderer->SetupAttachment(Root);

	ShipRailRenderer = CreateDefaultSubObject<USpriteRenderer>("ShipRailRenderer");
	ShipRailRenderer->SetupAttachment(Root);

	ShipRenderer->SetAutoSize(1.2f, true);
	ShipRenderer->SetPivot(EPivot::RIGHTBOTTOM);
	ShipRenderer->SetOrder(ERenderingOrder::BossMonster);

	ShipRailRenderer->SetAutoSize(1.2f, true);
	ShipRailRenderer->SetOrder(ERenderingOrder::BossMonsterBackFX1);
	ShipRailRenderer->SetPosition(float4(0.0f, 0.0f, 0.0f));
}

void ACaptainBrineybeardPhase1::AnimationInit()
{
	CreateAnimation();

}