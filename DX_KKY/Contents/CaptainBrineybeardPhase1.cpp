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
	ShipRenderer = CreateDefaultSubObject<USpriteRenderer>("ShipRenderer");
	ShipRenderer->SetupAttachment(Root);

	ShipRenderer->SetAutoSize(1.2f, true);
	ShipRenderer->SetPivot(EPivot::RIGHTBOTTOM);
	ShipRenderer->SetOrder(ERenderingOrder::BossMonster);

}

void ACaptainBrineybeardPhase1::AnimationInit()
{
	CreateAnimation();

}