#include "PreCompile.h"
#include "CagneyCarnation.h"

void ACagneyCarnation::StateInit()
{
	StateCreate();
	StartFunctionSet();
	UpdateFunctionSet();
	EndFunctionSet();


	// 
	State.ChangeState(FlowerBossState::Intro);
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

}

void ACagneyCarnation::UpdateFunctionSet()
{
	// Idle
	State.SetUpdateFunction(FlowerBossState::Idle, [this](float)
		{

		});

	//Intro
	State.SetUpdateFunction(FlowerBossState::Intro, [this](float)
		{

		});

	// FaceAttack
	State.SetUpdateFunction(FlowerBossState::FaceAttackHigh_Begin, [this](float)
		{

		});
	State.SetUpdateFunction(FlowerBossState::FaceAttackHigh_Idle, [this](float)
		{

		});
	State.SetUpdateFunction(FlowerBossState::FaceAttackHigh_End, [this](float)
		{

		});
}

void ACagneyCarnation::EndFunctionSet()
{

}