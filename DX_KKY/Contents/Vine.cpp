#include "PreCompile.h"
#include <EngineCore/DefaultSceneComponent.h>

#include "Vine.h"

AVine::AVine()
{
	BackVineRenderer = CreateDefaultSubObject<USpriteRenderer>("BackVineRenderer");
	BackVineRenderer->SetupAttachment(GetRoot());
	
	StemCollider = CreateDefaultSubObject<UCollision>("StemCollider");
	StemCollider->SetupAttachment(GetRoot());
}

AVine::~AVine()
{
}

void AVine::BeginPlay()
{
	Super::BeginPlay();

	AnimationInit();
	RendererInit();
	ColliderInit();
	StateInit();
}

void AVine::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}

void AVine::StateInit()
{
	State.CreateState(FlowerBossState::Vine_Wait);
	State.CreateState(FlowerBossState::Vine_GrowUp);

	State.SetStartFunction(FlowerBossState::Vine_Wait, [this]()
		{
			// front vine Renderer
			GetRenderer()->SetActive(false);
			// back vine Renderer
			BackVineRenderer->SetActive(false);
			//// front vine Collider
			//Collider->SetActive(false);
			//// vine sten Collider
			//StemCollider->SetActive(false);
		});
	State.SetStartFunction(FlowerBossState::Vine_GrowUp, [this]() {
		GetRenderer()->SetActive(true);
		BackVineRenderer->SetActive(true);

		GetRenderer()->ChangeAnimation(FlowerBossAniName::FrontVine_Begin);
		BackVineRenderer->ChangeAnimation(FlowerBossAniName::BackVine_Begin);
		});

	State.SetUpdateFunction(FlowerBossState::Vine_Wait, [](float) {});
	State.SetUpdateFunction(FlowerBossState::Vine_GrowUp, [](float) {});

	State.ChangeState(FlowerBossState::Vine_Wait);
}

void AVine::RendererInit()
{
	SetRendererAutoSize();
	SetRendererOrder(ERenderingOrder::BossMonsterObject2);
	SetRendererPivot(EPivot::BOT);

	BackVineRenderer->SetAutoSize(1.0f, true);
	BackVineRenderer->SetOrder(ERenderingOrder::Object3);
	BackVineRenderer->SetPivot(EPivot::BOT);
	BackVineRenderer->SetPosition(float4(0.0f, 20.0f, 0.0f));
}

void AVine::ColliderInit()
{
	//StemCollider
	//GetCollider
}

void AVine::AnimationInit()
{
	// front vine
	CreateAnimation(FAniInfo(FlowerBossAniName::FrontVine_Begin, "vineFrontBegin", 0.0416f), false);
	CreateAnimation(FAniInfo(FlowerBossAniName::FrontVine_Idle, "vineFrontIdle", 0.0416f));
	CreateAnimation(FAniInfo(FlowerBossAniName::FrontVine_Attack, "vineFrontAttack", 0.0416f),false);
	CreateRevAnimation(FAniInfo(FlowerBossAniName::FrontVine_AttackEnd, "vineFrontAttack", 0.0416f), false, 9, 0);
	CreateRevAnimation(FAniInfo(FlowerBossAniName::FrontVine_Dissapear, "vineFrontBegin", 0.0416f), false, 7, 0);

	GetRenderer()->SetLastFrameCallback(FlowerBossAniName::FrontVine_Begin, [this]()
		{
			GetRenderer()->ChangeAnimation(FlowerBossAniName::FrontVine_Idle);
		});

	// back vine
	BackVineRenderer->CreateAnimation(FlowerBossAniName::BackVine_Begin, "vineBackBegin", 0.0416f, false);
	BackVineRenderer->CreateAnimation(FlowerBossAniName::BackVine_Idle, "vineBackIdle", 0.0416f);
	BackVineRenderer->CreateAnimation(FlowerBossAniName::BackVine_Dissapear, "vineFrontBegin", 0.0416f, false);

	BackVineRenderer->SetLastFrameCallback(FlowerBossAniName::BackVine_Begin, [this]()
		{
			BackVineRenderer->ChangeAnimation(FlowerBossAniName::BackVine_Idle);
		});
}