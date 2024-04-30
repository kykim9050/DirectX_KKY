#include "PreCompile.h"

#include "CaptainBrineybeardPhase2.h"

void ACaptainBrineybeardPhase2::StateInit()
{
	StateCreate();
	StartFunctionSet();
	UpdateFunctionSet();
	EndFunctionSet();

	ShipState.ChangeState(PirateBossState::Ship_Phase2_Transforming);
}

void ACaptainBrineybeardPhase2::StateCreate()
{
	ShipState.CreateState(PirateBossState::Ship_Phase2_Transforming);
}

void ACaptainBrineybeardPhase2::StartFunctionSet()
{
	ShipState.SetStartFunction(PirateBossState::Ship_Phase2_Transforming, [this]()
		{
			ShipRenderer->ChangeAnimation(PirateBossAniName::Ship_Phase2_Transform_Idle);
		});
}

void ACaptainBrineybeardPhase2::UpdateFunctionSet()
{
	ShipState.SetUpdateFunction(PirateBossState::Ship_Phase2_Transforming, [this](float)
		{
			
		});
}

void ACaptainBrineybeardPhase2::EndFunctionSet()
{

}