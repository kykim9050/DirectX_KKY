#include "PreCompile.h"

#include "CaptainBrineybeardPhase1.h"


void ACaptainBrineybeardPhase1::StateInit()
{
	StateCreate();
	StartFunctionSet();
	UpdateFunctionSet();
	EndFunctionSet();

	ShipState.ChangeState(PirateBossState::Ship_Phase1_Idle);
	PirateState.ChangeState(PirateBossState::Pirate_Intro);
}

void ACaptainBrineybeardPhase1::StateCreate()
{
	// Ship State
	{
		ShipState.CreateState(PirateBossState::Ship_Phase1_Idle);
	}

	// Pirate
	{
		PirateState.CreateState(PirateBossState::Pirate_Intro);
		PirateState.CreateState(PirateBossState::Pirate_Laugh);
	}

}

void ACaptainBrineybeardPhase1::StartFunctionSet()
{
	// Ship State
	{
		ShipState.SetStartFunction(PirateBossState::Ship_Phase1_Idle, [this]()
			{
				ShipRenderer->ChangeAnimation(PirateBossAniName::Ship_Phase1_Idle);
			});
	}

	// Pirate
	{
		PirateState.SetStartFunction(PirateBossState::Pirate_Intro, [this]()
			{
				PirateRenderer->ChangeAnimation(PirateBossAniName::Pirate_Intro);
			});
		PirateState.SetStartFunction(PirateBossState::Pirate_Laugh, [this]()
			{
				PirateRenderer->ChangeAnimation(PirateBossAniName::Pirate_Laugh);
			});
	}
}

void ACaptainBrineybeardPhase1::UpdateFunctionSet()
{
	// Ship State
	{
		ShipState.SetUpdateFunction(PirateBossState::Ship_Phase1_Idle, std::bind(&ACaptainBrineybeardPhase1::Ship_Idle, this, std::placeholders::_1));
	}

	// Pirate
	{
		PirateState.SetUpdateFunction(PirateBossState::Pirate_Intro, [this](float)
			{
				if (true == PirateRenderer->IsCurAnimationEnd())
				{
					PirateState.ChangeState(PirateBossState::Pirate_Laugh);
					return;
				}
			});
		PirateState.SetUpdateFunction(PirateBossState::Pirate_Laugh, [this](float)
			{

			});
	}
}

void ACaptainBrineybeardPhase1::EndFunctionSet()
{

}

void ACaptainBrineybeardPhase1::Ship_Idle(float _DeltaTime)
{
	BlinkDelay -= _DeltaTime;

	if (0.0f >= BlinkDelay)
	{
		BlinkDelay = BlinkDelayInit + BlinkDelay;

		ShipRenderer->ChangeAnimation(PirateBossAniName::Ship_Phase1_Blink);
	}


	AccTime += _DeltaTime;

	AddActorLocation(float4(0.0f, 0.065f * sinf(AccTime * 1.5f), 0.0f));
}