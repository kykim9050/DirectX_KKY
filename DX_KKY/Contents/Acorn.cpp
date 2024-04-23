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
	State.CreateState(FlowerBossState::Acorn_Fly);
	State.CreateState(FlowerBossState::Acorn_Death);

	State.SetStartFunction(FlowerBossState::Acorn_Init, []() {});
	State.SetStartFunction(FlowerBossState::Acorn_Spawn, [this]()
		{
			ChangeAnimation(FlowerBossAniName::Acorn_Spawn);
		});
	State.SetStartFunction(FlowerBossState::Acorn_Fly, [this]()
		{
			BoundaryValue = GEngine->EngineWindow.GetWindowScale();

			float4 PlayerPos = UContentsFunction::GetStagePlayer()->GetActorLocation();
			float4 BulletPos = GetActorLocation();
			float4 TargetDir = (PlayerPos - BulletPos).Normalize2DReturn();

			ResVelocity = TargetDir * BulletSpeed;
			SetSpeedVec(ResVelocity);

			float Theta = UMath::GetInst().DirectionToDeg(TargetDir);
			SetActorRotation(float4(0.0f, 0.0f, Theta + 180));

			ChangeAnimation(FlowerBossAniName::Acorn_Fly);
		});
	State.SetStartFunction(FlowerBossState::Acorn_Death, [this]()
		{
			ChangeAnimation(FlowerBossAniName::Acorn_Death);
		});
	


	State.SetUpdateFunction(FlowerBossState::Acorn_Init, [this](float)
		{
			State.ChangeState(FlowerBossState::Acorn_Spawn);
			return;
		});
	State.SetUpdateFunction(FlowerBossState::Acorn_Spawn, [](float) {});
	State.SetUpdateFunction(FlowerBossState::Acorn_Fly, std::bind(&AAcorn::Flying, this, std::placeholders::_1));
	State.SetUpdateFunction(FlowerBossState::Acorn_Death, [](float) {});

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

	SetRendererFrameCallback(FlowerBossAniName::Acorn_Death, 9, [this]()
		{
			Destroy();
		});
}

void AAcorn::Flying(float _DeltaTime)
{
	if (BoundaryCheck(BoundaryValue))
	{
		State.ChangeState(FlowerBossState::Acorn_Death);
		return;
	}
	
	ResultMovementUpdate(_DeltaTime);
}