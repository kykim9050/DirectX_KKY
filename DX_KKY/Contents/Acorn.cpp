#include "PreCompile.h"

#include "Acorn.h"

AAcorn::AAcorn()
{
}

AAcorn::~AAcorn()
{
}

void AAcorn::BeginPlay()
{
	Super::BeginPlay();

	AnimationInit();
	RendererInit();
	ColliderInit();
	StateInit();
}

void AAcorn::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}

void AAcorn::StateInit()
{
	State.CreateState(FlowerBossState::Acorn_Init);
	State.CreateState(FlowerBossState::Acorn_Spawn);

	State.SetStartFunction(FlowerBossState::Acorn_Init, []() {});
	State.SetStartFunction(FlowerBossState::Acorn_Spawn, [this]()
		{
			ChangeAnimation(FlowerBossAniName::Acorn_Spawn);
		});

	State.SetUpdateFunction(FlowerBossState::Acorn_Init, [this](float)
		{
			State.ChangeState(FlowerBossState::Acorn_Spawn);
			return;
		});
	State.SetUpdateFunction(FlowerBossState::Acorn_Spawn, [](float) {});

	State.ChangeState(FlowerBossState::Acorn_Init);
}

void AAcorn::RendererInit()
{
	SetRendererAutoSize();
	SetRendererOrder(ERenderingOrder::MonsterBullet);
}

void AAcorn::ColliderInit()
{
	//SetColScale(float4(32.0f, 32.0f, 1.0f));
	//SetColGroup(ECollisionGroup::MonsterBullet);
	//SetColType(ECollisionType::CirCle);
}

void AAcorn::AnimationInit()
{
	CreateAnimation(FAniInfo(FlowerBossAniName::Acorn_Spawn, GSpriteName::Acorn_Spawn, 0.034f));
	CreateAnimation(FAniInfo(FlowerBossAniName::Acorn_Fly, GSpriteName::Acorn_Fly, 0.034f));
	CreateAnimation(FAniInfo(FlowerBossAniName::Acorn_Death, GSpriteName::Acorn_Death, 0.0416f), false);
}