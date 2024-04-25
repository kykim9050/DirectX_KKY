﻿#include "PreCompile.h"
#include <EngineCore/DefaultSceneComponent.h>

#include "Vine.h"

Vine::Vine()
{
	BackVineRenderer = CreateDefaultSubObject<USpriteRenderer>("BackVineRenderer");
	BackVineRenderer->SetupAttachment(GetRoot());
	
	StemCollider = CreateDefaultSubObject<UCollision>("StemCollider");
	StemCollider->SetupAttachment(GetRoot());
}

Vine::~Vine()
{
}

void Vine::BeginPlay()
{
	Super::BeginPlay();

	AnimationInit();
	RendererInit();
	ColliderInit();
	StateInit();
}

void Vine::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}

void Vine::StateInit()
{
	State.CreateState(FlowerBossState::Vine_Wait);
	State.CreateState(FlowerBossState::Vine_GrowUp);

	State.SetStartFunction(FlowerBossState::Vine_Wait, [this]()
		{
			// front vine Renderer
			GetRenderer()->SetActive(false);
			// back vine Renderer
			BackVineRenderer->SetActive(false);
			// front vine Collider
			Collider->SetActive(false);
			// vine sten Collider
			StemCollider->SetActive(false);
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

void Vine::RendererInit()
{
	SetRendererAutoSize();
	SetRendererOrder(ERenderingOrder::Object1);
	SetRendererPivot(EPivot::BOT);

	BackVineRenderer->SetAutoSize(1.0f, true);
	BackVineRenderer->SetOrder(ERenderingOrder::Object2);
	BackVineRenderer->SetPivot(EPivot::BOT);
}

void Vine::ColliderInit()
{
	//StemCollider
	//GetCollider
}

void Vine::AnimationInit()
{
	// front vine
	CreateAnimation(FAniInfo(FlowerBossAniName::FrontVine_Begin, "vineFrontBegin", 0.0416f), false);
	CreateAnimation(FAniInfo(FlowerBossAniName::FrontVine_Idle, "vineFrontIdle", 0.0416f));
	CreateAnimation(FAniInfo(FlowerBossAniName::FrontVine_Attack, "vineFrontAttack", 0.0416f),false);
	CreateRevAnimation(FAniInfo(FlowerBossAniName::FrontVine_AttackEnd, "vineFrontAttack", 0.0416f), false, 9, 0);
	CreateRevAnimation(FAniInfo(FlowerBossAniName::FrontVine_Dissapear, "vineFrontBegin", 0.0416f), false, 7, 0);

	// back vine
	CreateAnimation(FAniInfo(FlowerBossAniName::BackVine_Begin, "vineBackBegin", 0.0416f), false);
	CreateAnimation(FAniInfo(FlowerBossAniName::BackVine_Idle, "vineBackIdle", 0.0416f));
	CreateRevAnimation(FAniInfo(FlowerBossAniName::BackVine_Dissapear, "vineFrontBegin", 0.0416f), false, 13, 0);
}