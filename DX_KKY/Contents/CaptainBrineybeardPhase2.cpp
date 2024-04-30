#include "PreCompile.h"
#include <EngineCore/DefaultSceneComponent.h>

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

	ShipRenderer->SetAutoSize(1.2f, true);
	ShipRenderer->SetPivot(EPivot::RIGHTBOTTOM);
	ShipRenderer->SetOrder(ERenderingOrder::BossMonster);
	ShipRenderer->SetPosition(GRendererPos::Ship_Phase1_RelativePos);
}

void ACaptainBrineybeardPhase2::AnimationInit()
{
	CreateAnimation();
}

void ACaptainBrineybeardPhase2::ColliderInit()
{

}

void ACaptainBrineybeardPhase2::DebugUpdate()
{

}