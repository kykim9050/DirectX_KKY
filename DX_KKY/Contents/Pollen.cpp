#include "PreCompile.h"

#include "Pollen.h"

APollen::APollen()
{
	DefineParryableUnit();

}

APollen::~APollen()
{
}

void APollen::BeginPlay()
{
	Super::BeginPlay();

	AnimationInit();
	RendererInit();
	ColliderInit();
	StateInit();
}

void APollen::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void APollen::StateInit()
{
	State.CreateState(FlowerBossState::Pollen_Throwing);

	State.SetStartFunction(FlowerBossState::Pollen_Throwing, [this]()
		{
			{
				SetHorizontalDir(float4::Left);
				SetVerticalDir(float4::Up);
				SetHorizontalSpeed(350.0f);
				SetSpeedVec(GetHorizontalDir() * GetHorizontalSpeed());
			}
			Renderer->ChangeAnimation(FlowerBossAniName::Pollen + Color);
		});

	State.SetUpdateFunction(FlowerBossState::Pollen_Throwing, std::bind(&APollen::Throwing, this, std::placeholders::_1));

	State.ChangeState(FlowerBossState::Pollen_Throwing);
}

void APollen::RendererInit()
{
	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetOrder(ERenderingOrder::MonsterBullet);
}

void APollen::ColliderInit()
{
	Collision->SetScale(float4(32.0f, 32.0f, 1.0f));
	Collision->SetCollisionGroup(ECollisionGroup::MonsterBullet);
	Collision->SetCollisionType(ECollisionType::Rect);
}

void APollen::AnimationInit()
{
	Renderer->CreateAnimation(FlowerBossAniName::Pollen + Color, "Pollen" + Color, 0.0678f);
}

void APollen::DefineParryableUnit()
{
	// 25% 확률로 Parryable 이 된다
	RandomValue = UMath::RandomReturnInt(0, 3);

	if (NOT_DEFINE == RandomValue)
	{
		MsgBoxAssert("Pollen의 색이 정상적으로 지정되지 않았습니다.");
		return;
	}

	if (PARRYABLE_VALUE == RandomValue)
	{
		Color = "_Pink";
		SetParryableObject();
		return;
	}
	else
	{
		Color = "_White";
		return;
	}
}

void APollen::Throwing(float _DeltaTime)
{
	if (true == BoundaryCheck(BoundaryValue, 100.0f))
	{
		Destroy();
		return;
	}
	
	if (0.0f == _DeltaTime)
	{
		return;
	}

	AccTime += _DeltaTime;

	AddActorLocation(float4(0.0f, 0.2f * sinf(AccTime * 5.0f), 0.0f));
	SetActorRotation(float4(0.0f, 0.0f, 2.0f * AccTime * UEngineMath::RToD));
	ResultMovementUpdate(_DeltaTime);
}