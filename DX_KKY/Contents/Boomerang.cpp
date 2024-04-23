#include "PreCompile.h"

#include "Boomerang.h"

ABoomerang::ABoomerang()
{
}

ABoomerang::~ABoomerang()
{
}

void ABoomerang::BeginPlay()
{
	Super::BeginPlay();

	AnimationInit();
	RendererInit();
	ColliderInit();
	StateInit();
}

void ABoomerang::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}

void ABoomerang::StateInit()
{
	State.CreateState(FlowerBossState::Boomerang_Init);
	State.CreateState(FlowerBossState::Boomerang_Spawn);
	State.CreateState(FlowerBossState::Boomerang_Throw);
	//State.CreateState(FlowerBossState::Boomerang_Destroy);

	State.SetStartFunction(FlowerBossState::Boomerang_Init, []() {});
	State.SetStartFunction(FlowerBossState::Boomerang_Spawn, [this]()
		{
			ChangeAnimation(FlowerBossAniName::Boomerang_Rotate);
		});
	State.SetStartFunction(FlowerBossState::Boomerang_Throw, [this]()
		{
			SetSpeedVec(ThrowingDir * ThrowingSpeed);
		});

	State.SetUpdateFunction(FlowerBossState::Boomerang_Init, [this](float)
		{
			State.ChangeState(FlowerBossState::Boomerang_Spawn);
			return;
		});
	State.SetUpdateFunction(FlowerBossState::Boomerang_Spawn, [](float) {});
	State.SetUpdateFunction(FlowerBossState::Boomerang_Throw, std::bind(&ABoomerang::Throwing, this, std::placeholders::_1));


	State.ChangeState(FlowerBossState::Boomerang_Init);
}

void ABoomerang::RendererInit()
{
	SetRendererAutoSize();
	SetRendererOrder(ERenderingOrder::MonsterBullet);
}

void ABoomerang::ColliderInit()
{
	SetColScale(GColliderScale::Boomerang_ColScale);
	SetColGroup(ECollisionGroup::MonsterBullet);
	SetColType(ECollisionType::Rect);
	SetColPosition(float4(0.0f, 0.0f, 0.0f));
}

void ABoomerang::AnimationInit()
{
	CreateAnimation(FAniInfo(FlowerBossAniName::Boomerang_Rotate, GSpriteName::Boomerang_Rotate, 0.0416f));
}

void ABoomerang::Throwing(float _DeltaTime)
{

	ResultMovementUpdate(_DeltaTime);
}