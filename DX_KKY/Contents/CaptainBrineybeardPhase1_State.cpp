#include "PreCompile.h"

#include "CaptainBrineybeardPhase1.h"


void ACaptainBrineybeardPhase1::StateInit()
{
	StateCreate();
	StartFunctionSet();
	UpdateFunctionSet();
	EndFunctionSet();

	ShipState.ChangeState(PirateBossState::Ship_Phase1_Idle);
}

void ACaptainBrineybeardPhase1::StateCreate()
{
	// Ship State
	{
		ShipState.CreateState(PirateBossState::Ship_Phase1_Idle);
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
}

void ACaptainBrineybeardPhase1::UpdateFunctionSet()
{
	// Ship State
	{
		ShipState.SetUpdateFunction(PirateBossState::Ship_Phase1_Idle, std::bind(&ACaptainBrineybeardPhase1::Ship_Idle, this, std::placeholders::_1));
	}
}

void ACaptainBrineybeardPhase1::EndFunctionSet()
{
	// Ship State
}

void ACaptainBrineybeardPhase1::Ship_Idle(float _DeltaTime)
{

	AccTime += _DeltaTime;

	//AddActorLocation(float4(0.0f, 0.07f * sinf(AccTime * 0.5f), 0.0f));
}