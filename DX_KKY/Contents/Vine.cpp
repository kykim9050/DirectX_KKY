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
	State.CreateState(FlowerBossState::Vine_WaitAttack);
	State.CreateState(FlowerBossState::Vine_Attack);

	State.SetStartFunction(FlowerBossState::Vine_Wait, [this]()
		{
			// front vine Renderer
			GetRenderer()->SetActive(false);
			// back vine Renderer
			BackVineRenderer->SetActive(false);
		});
	State.SetStartFunction(FlowerBossState::Vine_GrowUp, [this]() {
		GetRenderer()->SetActive(true);
		BackVineRenderer->SetActive(true);
		GetRenderer()->ChangeAnimation(FlowerBossAniName::FrontVine_Begin);
		BackVineRenderer->ChangeAnimation(FlowerBossAniName::BackVine_Begin);
		});
	State.SetStartFunction(FlowerBossState::Vine_WaitAttack, [this]()
		{
			AttackDelay = UMath::GetInst().RandomReturnFloat(1.0f, 1.5f);
		});
	State.SetStartFunction(FlowerBossState::Vine_Attack, [this]()
		{
			//// front vine Collider
			Collider->SetActive(true);
			//// vine stem Collider
			StemCollider->SetActive(true);
			Renderer->ChangeAnimation(FlowerBossAniName::FrontVine_Attack);
		});

	State.SetUpdateFunction(FlowerBossState::Vine_Wait, [](float) {});
	State.SetUpdateFunction(FlowerBossState::Vine_GrowUp, [](float) {});
	State.SetUpdateFunction(FlowerBossState::Vine_WaitAttack, std::bind(&AVine::WaitAttack, this, std::placeholders::_1));
	State.SetUpdateFunction(FlowerBossState::Vine_Attack, [](float) {});

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

	// front vine Renderer
	GetRenderer()->SetActive(false);
	// back vine Renderer
	BackVineRenderer->SetActive(false);
}

void AVine::ColliderInit()
{
	GetCollider()->SetScale(GColliderScale::VineAttack_ColScale);
	GetCollider()->SetCollisionGroup(ECollisionGroup::Trap);
	GetCollider()->SetCollisionType(ECollisionType::Rect);
	GetCollider()->SetPosition(GColliderPosInfo::VineAttack_RelativePos);

	StemCollider->SetScale(GColliderScale::VineStem_ColScale);
	StemCollider->SetCollisionGroup(ECollisionGroup::Trap);
	StemCollider->SetCollisionType(ECollisionType::Rect);
	StemCollider->SetPosition(GColliderPosInfo::VineStem_RelativePos);

	//// front vine Collider
	Collider->SetActive(false);
	//// vine sten Collider
	StemCollider->SetActive(false);
}

void AVine::AnimationInit()
{
	// front vine
	CreateAnimation(FAniInfo(FlowerBossAniName::FrontVine_Begin, "vineFrontBegin", 0.0416f), false);
	CreateAnimation(FAniInfo(FlowerBossAniName::FrontVine_Idle, "vineFrontIdle", 0.0416f));
	CreateAnimation(FAniInfo(FlowerBossAniName::FrontVine_Attack, "vineFrontAttack", 0.0416f),false);
	CreateRevAnimation(FAniInfo(FlowerBossAniName::FrontVine_AttackEnd, "vineFrontAttack", 0.0416f), false, 9, 0);
	CreateRevAnimation(FAniInfo(FlowerBossAniName::FrontVine_Dissapear, "vineFrontBegin", 0.0416f), false, 7, 0);

	GetRenderer()->SetFrameCallback(FlowerBossAniName::FrontVine_Begin, 8, [this]()
		{
			GetRenderer()->ChangeAnimation(FlowerBossAniName::FrontVine_Idle);
		});
	GetRenderer()->SetFrameCallback(FlowerBossAniName::FrontVine_Attack, 10, [this]()
		{
			GetRenderer()->ChangeAnimation(FlowerBossAniName::FrontVine_AttackEnd);
		});
	GetRenderer()->SetFrameCallback(FlowerBossAniName::FrontVine_AttackEnd, 10, [this]()
		{
			//// front vine Collider
			Collider->SetActive(false);
			GetRenderer()->ChangeAnimation(FlowerBossAniName::FrontVine_Dissapear);
			BackVineRenderer->ChangeAnimation(FlowerBossAniName::BackVine_Dissapear);
		});
	GetRenderer()->SetFrameCallback(FlowerBossAniName::FrontVine_Dissapear, 8, [this]()
		{
			StemCollider->SetActive(false);
			GetRenderer()->SetActive(false);
		});



	// back vine
	BackVineRenderer->CreateAnimation(FlowerBossAniName::BackVine_Begin, "vineBackBegin", 0.0416f, false);
	BackVineRenderer->CreateAnimation(FlowerBossAniName::BackVine_Idle, "vineBackIdle", 0.0416f);
	BackVineRenderer->CreateAnimation(FlowerBossAniName::BackVine_Dissapear, "vineBackBegin", 0.0416f, false, 13, 0);

	BackVineRenderer->SetFrameCallback(FlowerBossAniName::BackVine_Begin, 14, [this]()
		{
			BackVineRenderer->ChangeAnimation(FlowerBossAniName::BackVine_Idle);
			State.ChangeState(FlowerBossState::Vine_WaitAttack);
		});
	BackVineRenderer->SetFrameCallback(FlowerBossAniName::BackVine_Dissapear, 14, [this]()
		{
			State.ChangeState(FlowerBossState::Vine_Wait);
		});
}

void AVine::WaitAttack(float _DeltaTime)
{
	AttackDelay -= _DeltaTime;

	if (0.0f >= AttackDelay)
	{
		AttackDelay = 0.0f;

		State.ChangeState(FlowerBossState::Vine_Attack);
		return;
	}
}