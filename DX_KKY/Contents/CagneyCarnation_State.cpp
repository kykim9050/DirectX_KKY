#include "PreCompile.h"
#include "CagneyCarnation.h"

void ACagneyCarnation::StateInit()
{
	StateCreate();
	StartFunctionSet();
	UpdateFunctionSet();
	EndFunctionSet();

	//State.ChangeState(FlowerBossState::Intro);
	State.ChangeState(FlowerBossState::Gatling_Begin);
}


void ACagneyCarnation::StateCreate()
{
	// Intro
	// Idle
	State.CreateState(FlowerBossState::Intro);
	State.CreateState(FlowerBossState::Idle);

	// FaceAttack
	State.CreateState(FlowerBossState::FaceAttackHigh_Begin);
	State.CreateState(FlowerBossState::FaceAttackHigh_Idle);
	State.CreateState(FlowerBossState::FaceAttackHigh_End);
	InsertAttackPattern(EAttackPattern::FaceAttack_High, FlowerBossState::FaceAttackHigh_Begin);
	State.CreateState(FlowerBossState::FaceAttackLow_Begin);
	State.CreateState(FlowerBossState::FaceAttackLow_Idle);
	State.CreateState(FlowerBossState::FaceAttackLow_End);
	InsertAttackPattern(EAttackPattern::FaceAttack_Low, FlowerBossState::FaceAttackLow_Begin);

	// Gatling
	State.CreateState(FlowerBossState::Gatling_Begin);
	State.CreateState(FlowerBossState::Gatling_Idle);
	State.CreateState(FlowerBossState::Gatling_End);
	InsertAttackPattern(EAttackPattern::Gatling, FlowerBossState::Gatling_Begin);
}

void ACagneyCarnation::StartFunctionSet()
{
	//Intro
	State.SetStartFunction(FlowerBossState::Intro, [this]()
		{
			Renderer->ChangeAnimation(FlowerBossAniName::Flower_Intro);
		});

	//Idle
	State.SetStartFunction(FlowerBossState::Idle, [this]()
		{
			Renderer->ChangeAnimation(FlowerBossAniName::Flower_Idle);
		});

	// FaceAttack
	State.SetStartFunction(FlowerBossState::FaceAttackHigh_Begin, [this]()
		{
			Renderer->ChangeAnimation(FlowerBossAniName::Flower_FaceAttackHigh_Begin);
		});
	State.SetStartFunction(FlowerBossState::FaceAttackHigh_Idle, [this]()
		{
			Renderer->ChangeAnimation(FlowerBossAniName::Flower_FaceAttackHigh_Idle);
		});
	State.SetStartFunction(FlowerBossState::FaceAttackHigh_End, [this]()
		{
			Renderer->ChangeAnimation(FlowerBossAniName::Flower_FaceAttackHigh_End);
		});

	State.SetStartFunction(FlowerBossState::FaceAttackLow_Begin, [this]()
		{
			AddActorLocation(FVector(0.0f, -110.f, 0.0f));
			Renderer->ChangeAnimation(FlowerBossAniName::Flower_FaceAttackLow_Begin);
		});
	State.SetStartFunction(FlowerBossState::FaceAttackLow_Idle, [this]()
		{
			Renderer->ChangeAnimation(FlowerBossAniName::Flower_FaceAttackLow_Idle);
		});
	State.SetStartFunction(FlowerBossState::FaceAttackLow_End, [this]()
		{
			Renderer->ChangeAnimation(FlowerBossAniName::Flower_FaceAttackLow_End);
		});

	// Gatling
	State.SetStartFunction(FlowerBossState::Gatling_Begin, [this]()
		{
			Renderer->ChangeAnimation(FlowerBossAniName::Flower_Gatling_Begin);
		});
	State.SetStartFunction(FlowerBossState::Gatling_Idle, [this]()
		{
			Renderer->ChangeAnimation(FlowerBossAniName::Flower_Gatling_Idle);
		});
	State.SetStartFunction(FlowerBossState::Gatling_End, [this]()
		{
			Renderer->ChangeAnimation(FlowerBossAniName::Flower_Gatling_End);
		});
}

void ACagneyCarnation::UpdateFunctionSet()
{
	// Idle
	State.SetUpdateFunction(FlowerBossState::Idle, std::bind(&ACagneyCarnation::Idle, this, std::placeholders::_1));

	//Intro
	State.SetUpdateFunction(FlowerBossState::Intro, [this](float){});

	// FaceAttack
	State.SetUpdateFunction(FlowerBossState::FaceAttackHigh_Begin, [this](float){});
	State.SetUpdateFunction(FlowerBossState::FaceAttackHigh_Idle, std::bind(&ACagneyCarnation::FaceAttackHigh_Idle, this, std::placeholders::_1));
	State.SetUpdateFunction(FlowerBossState::FaceAttackHigh_End, [this](float){});
	State.SetUpdateFunction(FlowerBossState::FaceAttackLow_Begin, [this](float){});
	State.SetUpdateFunction(FlowerBossState::FaceAttackLow_Idle, std::bind(&ACagneyCarnation::FaceAttackLow_Idle, this, std::placeholders::_1));
	State.SetUpdateFunction(FlowerBossState::FaceAttackLow_End, [this](float) {});

	// Gatling
	State.SetUpdateFunction(FlowerBossState::Gatling_Begin, [this](float) {});
	State.SetUpdateFunction(FlowerBossState::Gatling_Idle, std::bind(&ACagneyCarnation::Gatling_Idle, this, std::placeholders::_1));
	State.SetUpdateFunction(FlowerBossState::Gatling_End, [this](float) {});
}

void ACagneyCarnation::EndFunctionSet()
{

}

void ACagneyCarnation::Idle(float _DeltaTime)
{
	P1_ChangeDelay -= _DeltaTime;

	if (0.0f >= P1_ChangeDelay)
	{
		int PatternNum = UMath::GetInst().RandomReturnInt(0, EAttackPattern::Max);

		P1_ChangeDelay = P1_ChangeDelayValue;
		State.ChangeState(AttackPattern[PatternNum]);
		return;
	}
}

void ACagneyCarnation::FaceAttackHigh_Idle(float _DeltaTime)
{
	FaceAttackDelay -= _DeltaTime;

	if (0.0f >= FaceAttackDelay)
	{
		FaceAttackDelay = FaceAttackDelayValue;
		State.ChangeState(FlowerBossState::FaceAttackHigh_End);
		return;
	}
}

void ACagneyCarnation::FaceAttackLow_Idle(float _DeltaTime)
{
	FaceAttackDelay -= _DeltaTime;

	if (0.0f >= FaceAttackDelay)
	{
		FaceAttackDelay = FaceAttackDelayValue;
		State.ChangeState(FlowerBossState::FaceAttackLow_End);
		return;
	}
}

void ACagneyCarnation::Gatling_Idle(float _DeltaTime)
{
	GatlingTime -= _DeltaTime;

	if (0.0f >= GatlingTime)
	{
		GatlingTime = GatlingTimeValue;
		State.ChangeState(FlowerBossState::Gatling_End);
		return;
	}
}