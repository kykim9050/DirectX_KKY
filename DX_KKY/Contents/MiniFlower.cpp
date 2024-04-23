#include "PreCompile.h"

#include "MiniFlower.h"
#include "MiniFlowerBullet.h"

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
	State.CreateState(FlowerBossState::MiniFlower_Rise);
	State.CreateState(FlowerBossState::MiniFlower_Fly);
	State.CreateState(FlowerBossState::MiniFlower_Spit);

	State.SetStartFunction(FlowerBossState::MiniFlower_Spawn, [this]()
		{
			ChangeAnimation(FlowerBossAniName::MiniFlower_Spawn);
		});
	State.SetStartFunction(FlowerBossState::MiniFlower_Rise, [this]()
		{
			ChangeAnimation(FlowerBossAniName::MiniFlower_Fly);
		});
	State.SetStartFunction(FlowerBossState::MiniFlower_Fly, [this]()
		{
			if (FlowerBossState::MiniFlower_Spit == PrevState)
			{
				ChangeAnimation(FlowerBossAniName::MiniFlower_Fly);
			}
		});
	State.SetStartFunction(FlowerBossState::MiniFlower_Spit, [this]()
		{
			ChangeAnimation(FlowerBossAniName::MiniFlower_Spit);
		});


	State.SetUpdateFunction(FlowerBossState::MiniFlower_Spawn, [this](float) {});
	State.SetUpdateFunction(FlowerBossState::MiniFlower_Rise, std::bind(&AMiniFlower::Rising, this, std::placeholders::_1));
	State.SetUpdateFunction(FlowerBossState::MiniFlower_Fly, std::bind(&AMiniFlower::Flying, this, std::placeholders::_1));
	State.SetUpdateFunction(FlowerBossState::MiniFlower_Spit, [this](float) {});

	State.SetEndFunction(FlowerBossState::MiniFlower_Rise, [this]() {
		SetJumpVec(float4::Zero);
		});
	State.SetEndFunction(FlowerBossState::MiniFlower_Fly, [this]() {
		SetSpeedVec(float4::Zero);
		});
	State.SetEndFunction(FlowerBossState::MiniFlower_Spit, [this]() {
		PrevState = State.GetCurStateName();
		});

	State.ChangeState(FlowerBossState::MiniFlower_Spawn);
}

void AMiniFlower::RendererInit()
{
	SetRendererAutoSize();
	SetRendererOrder(ERenderingOrder::Monster1);
	//SetRendererPivot(EPivot::BOT);
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

	SetRendererFrameCallback(FlowerBossAniName::MiniFlower_Spawn, 5, [this]()
		{
			State.ChangeState(FlowerBossState::MiniFlower_Rise);
		});
	SetRendererFrameCallback(FlowerBossAniName::MiniFlower_Spit, 10, [this]()
		{
			// 패링 가능한 총알 발사
			CreateBullet();
		});
	SetRendererFrameCallback(FlowerBossAniName::MiniFlower_Spit, 17, [this]()
		{
			ChangeAnimation(FlowerBossState::MiniFlower_RevSpit);
		});
	SetRendererFrameCallback(FlowerBossAniName::MiniFlower_RevSpit, 17, [this]()
		{
			State.ChangeState(FlowerBossState::MiniFlower_Fly);
		});
}

void AMiniFlower::Rising(float _DeltaTime)
{
	float4 MyPos = GetActorLocation();
	MyPos.Y *= -1;

	if (MyPos.Y <= FlowerBossStageValue::MiniFlower_RisingEnd_Height) {
		State.ChangeState(FlowerBossState::MiniFlower_Fly);
		return;
	}

	SetJumpVec(float4::Up * UpSpeed);
	ResultMovementUpdate(_DeltaTime);
}

void AMiniFlower::Flying(float _DeltaTime)
{
	SpitDelay -= _DeltaTime;

	if (0.0f >= SpitDelay)
	{
		SpitDelay = SpitDelayInit;

		State.ChangeState(FlowerBossState::MiniFlower_Spit);
		return;
	}

	float4 MyPos = GetActorLocation();

	if (MyPos.X <= FlowerBossStageValue::MiniFlower_Flying_XBound_Min)
	{
		AddActorLocation(float4::Right);
		FlyingDir = float4::Right;
	}
	else if (MyPos.X >= FlowerBossStageValue::MiniFlower_Flying_XBound_Max)
	{
		AddActorLocation(float4::Left);
		FlyingDir = float4::Left;
	}

	SetSpeedVec(FlyingDir * FlyingSpeed);
	ResultMovementUpdate(_DeltaTime);
}

void AMiniFlower::ResultMovementUpdate(float _DeltaTime)
{
	Super::ResultMovementUpdate(_DeltaTime);
}

void AMiniFlower::CreateBullet()
{
	AMiniFlowerBullet* Bullet = GetWorld()->SpawnActor<AMiniFlowerBullet>("MiniFlowerBullet").get();
	Bullet->SetActorLocation(GetActorLocation());
}