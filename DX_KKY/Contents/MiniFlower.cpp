#include "PreCompile.h"

#include "MiniFlower.h"

AMiniFlower::AMiniFlower()
{
}

AMiniFlower::~AMiniFlower()
{
}

void AMiniFlower::BeginPlay()
{
	Super::BeginPlay();

	AnimationInit();
	RendererInit();
	ColliderInit();
	StateInit();
}

void AMiniFlower::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}

void AMiniFlower::StateInit()
{
	State.CreateState(FlowerBossState::MiniFlower_Spawn);

	State.SetStartFunction(FlowerBossState::MiniFlower_Spawn, [this]()
		{
			ChangeAnimation(FlowerBossAniName::MiniFlower_Spawn);
		});

	State.SetUpdateFunction(FlowerBossState::MiniFlower_Spawn, [this](float) {});

	State.ChangeState(FlowerBossState::MiniFlower_Spawn);
}

void AMiniFlower::RendererInit()
{
	SetRendererAutoSize();
	SetRendererOrder(ERenderingOrder::Monster1);
	SetRendererPivot(EPivot::BOT);
}

void AMiniFlower::ColliderInit()
{

}

void AMiniFlower::AnimationInit()
{

	CreateAnimation(FAniInfo(FlowerBossAniName::MiniFlower_Spawn , "MiniFlowerSpawn", 0.0416f), false);
	CreateAnimation(FAniInfo(FlowerBossAniName::MiniFlower_Fly, "MiniFlowerFly", 0.067f));
	CreateAnimation(FAniInfo(FlowerBossAniName::MiniFlower_Death, "MiniFlowerDeath", 0.0416f), false);
	CreateAnimation(FAniInfo(FlowerBossAniName::MiniFlower_Spit, "MiniFlowerSpit", 0.0416f), false);
	CreateRevAnimation(FAniInfo(FlowerBossAniName::MiniFlower_RevSpit, "MiniFlowerSpit", 0.0416f), false, 16, 0);
}