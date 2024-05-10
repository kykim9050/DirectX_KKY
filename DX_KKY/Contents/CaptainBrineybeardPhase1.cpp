#include "PreCompile.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/Collision.h>

#include "CaptainBrineybeardPhase1.h"
#include "FXBase.h"
#include "CannonBall.h"
#include "OctopusBullet.h"
#include "Shark.h"
#include "CallSeaDogs.h"
#include "PirateLevelMode.h"
#include "PirateLevelDebugWindow.h"

ACaptainBrineybeardPhase1::ACaptainBrineybeardPhase1()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");
	SetRoot(Root);

	SetHp(300);
	RendererInit();
	ColliderInit();
	SetGetHitFunction(std::bind(&ACaptainBrineybeardPhase1::AfterHitFlash, this));
}

ACaptainBrineybeardPhase1::~ACaptainBrineybeardPhase1()
{
}

void ACaptainBrineybeardPhase1::BeginPlay()
{
	Super::BeginPlay();

	APirateLevelMode::DebugWindow->SetOtherSetFunction(std::bind(&ACaptainBrineybeardPhase1::Dbg_ChangePattern, this, std::placeholders::_1));

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

void ACaptainBrineybeardPhase1::CreateWhistleEffect()
{
	AFXBase* WhistleEffect = GetWorld()->SpawnActor<AFXBase>("WhistleEffect", static_cast<int>(EActorType::FX)).get();
	WhistleEffect->FXInit(ERenderingOrder::BossMonsterFrontFX1, FAniInfo(PirateBossAniName::Pirate_Whistle_Effect, GSpriteName::Pirate_Whistle_Effect, 0.047f));
	WhistleEffect->SetImgPivot(EPivot::RIGHT);
	WhistleEffect->SetActorLocation(GetActorLocation() + GRendererPos::Pirate_WhistleEff_RelativePos);
}

void ACaptainBrineybeardPhase1::CreateCannonBall()
{
	ACannonBall* CannonBall = GetWorld()->SpawnActor<ACannonBall>("ACannonBall", static_cast<int>(EActorType::MonsterBullet)).get();
	CannonBall->SetActorLocation(GetActorLocation() + GActorPosValue::CannonBall_RelativePos);
}

void ACaptainBrineybeardPhase1::CreateOctopusBullet()
{
	AOctopusBullet* NewOctoBullet = GetWorld()->SpawnActor<AOctopusBullet>("NewOctoBullet", static_cast<int>(EActorType::MonsterBullet)).get();
	NewOctoBullet->SetActorLocation(GetActorLocation() + GActorPosValue::OctoBullet_RelativePos);
}

void ACaptainBrineybeardPhase1::Phase1_EndSetting()
{
	PirateRenderer->SetActive(false);
	PirateTopRenderer->SetActive(false);
	ShipRailRenderer->SetActive(false);
	ShipSailRenderer->SetActive(false);
	ShipMastRenderer->SetActive(false);
	MainCollider->SetActive(false);
}

void ACaptainBrineybeardPhase1::SpawnShark()
{
	AShark* Shark = GetWorld()->SpawnActor<AShark>("Shark", EActorType::Monster).get();
	Shark->SetActorLocation(GActorPosValue::Shark_Init_Pos);
}

void ACaptainBrineybeardPhase1::SpawnSeaDogs()
{
	std::shared_ptr<ACallSeaDogs> SeaDogs = GetWorld()->SpawnActor<ACallSeaDogs>("SeaDogs", EActorType::Monster);
}

void ACaptainBrineybeardPhase1::AfterHitFlash()
{
	PirateRenderer->SetPlusColor(GColorValue::AttackColor);
	PirateTopRenderer->SetPlusColor(GColorValue::AttackColor);

	DelayCallBack(0.05f, [this]()
		{
			PirateRenderer->SetPlusColor(GColorValue::AttackRestoreColor);
		});
	DelayCallBack(0.05f, [this]()
		{
			PirateTopRenderer->SetPlusColor(GColorValue::AttackRestoreColor);
		});		
}

void ACaptainBrineybeardPhase1::Dbg_ChangePattern(int _PatternNum)
{
	if (-1 != PatternNum)
	{
		return;
	}

	PatternNum = _PatternNum;
}

void ACaptainBrineybeardPhase1::Dbg_ChangeState()
{
	switch (PatternNum)
	{
	case static_cast<int>(EPirateBossPattern::OctopusShootAtt):
	{
		int a = 0;
		break;
	}
	case static_cast<int>(EPirateBossPattern::ShootCanonBall):
		break;
	case static_cast<int>(EPirateBossPattern::Phase2):
		break;
	default:
		MsgBoxAssert("지정되지 않은 패턴을 실행하려고 했습니다.");
		break;
	}

	Dbg_PatternSwitchDelay = Dbg_PatternSwitchDelayInit;
	PatternNum = -1;
	return;
}