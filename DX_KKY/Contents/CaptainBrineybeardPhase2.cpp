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

	JawRenderer = CreateDefaultSubObject<USpriteRenderer>("JawRenderer");
	JawRenderer->SetupAttachment(Root);

	UvulaRenderer = CreateDefaultSubObject<USpriteRenderer>("JawRenderer");
	UvulaRenderer->SetupAttachment(Root);


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
	//UvulaRenderer->SetPivot(EPivot::RIGHTTOP);
	UvulaRenderer->SetOrder(ERenderingOrder::Monster1);
	UvulaRenderer->SetPosition(/*GRendererPos::*/float4(-400.0f, 300.0f, 0.0f));
	UvulaRenderer->SetActive(false);
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