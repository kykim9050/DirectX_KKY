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
	ShipState.CreateState(PirateBossState::Ship_Phase2_Transforming_End);
	ShipState.CreateState(PirateBossState::Ship_Phase2_Idle);
	ShipState.CreateState(PirateBossState::Ship_phase2_LazarAtt_Begin);
	ShipState.CreateState(PirateBossState::Ship_phase2_LazarAtt_Charging);
	ShipState.CreateState(PirateBossState::Ship_phase2_LazarAtt_ChargingEnd);
	ShipState.CreateState(PirateBossState::Ship_phase2_LazarAttack);
	ShipState.CreateState(PirateBossState::Ship_phase2_LazarAttack_End);
}

void ACaptainBrineybeardPhase2::StartFunctionSet()
{
	ShipState.SetStartFunction(PirateBossState::Ship_Phase2_Transforming, [this]()
		{
			ShipRenderer->ChangeAnimation(PirateBossAniName::Ship_Phase2_Transform_Idle);
		});
	ShipState.SetStartFunction(PirateBossState::Ship_Phase2_Transforming_End, [this]()
		{
			ShipRenderer->ChangeAnimation(PirateBossAniName::Ship_Phase2_Transform_End);
		});
	ShipState.SetStartFunction(PirateBossState::Ship_Phase2_Idle, [this]()
		{
			ShipRenderer->ChangeAnimation(PirateBossAniName::Ship_Phase2_Idle);
		
			JawRenderer->ChangeAnimation(PirateBossAniName::Ship_Phase2_JawIdle);
			JawRenderer->SetActive(true);

			UvulaRenderer->ChangeAnimation(PirateBossAniName::Uvula_Idle);
			UvulaRenderer->SetActive(true);
		});
	ShipState.SetStartFunction(PirateBossState::Ship_phase2_LazarAtt_Begin, [this]()
		{
			ShipRenderer->ChangeAnimation(PirateBossAniName::Ship_Phase2_LazarAtt_Begin);
		});
	ShipState.SetStartFunction(PirateBossState::Ship_phase2_LazarAtt_Charging, [this]()
		{
			ShipRenderer->ChangeAnimation(PirateBossAniName::Ship_Phase2_LazarAtt_Charging);
		});
	ShipState.SetStartFunction(PirateBossState::Ship_phase2_LazarAtt_ChargingEnd, [this]()
		{
			ShipRenderer->ChangeAnimation(PirateBossAniName::Ship_Phase2_LazarAtt_ChargingEnd);
		});
	ShipState.SetStartFunction(PirateBossState::Ship_phase2_LazarAttack, [this]()
		{
			ShipRenderer->ChangeAnimation(PirateBossAniName::Ship_Phase2_LazarAttack1);

			LazarRenderer->AnimationReset();
			LazarRenderer->SetActive(true);
			LazarRenderer->ChangeAnimation(PirateBossAniName::Ship_Phase2_Lazar_Begin);
		});
	ShipState.SetStartFunction(PirateBossState::Ship_phase2_LazarAttack_End, [this]()
		{
			LazarCollider->SetActive(false);
			LazarRenderer->ChangeAnimation(PirateBossAniName::Ship_Phase2_Lazar_End);

			ShipRenderer->ChangeAnimation(PirateBossAniName::Ship_Phase2_LazarAttack_End);
		});
}

void ACaptainBrineybeardPhase2::UpdateFunctionSet()
{
	ShipState.SetUpdateFunction(PirateBossState::Ship_Phase2_Transforming, [this](float)
		{
			if (true == ShipRenderer->IsCurAnimationEnd())
			{
				if (RoarTime <= RoarCount)
				{
					RoarCount = 0;
					ShipState.ChangeState(PirateBossState::Ship_Phase2_Transforming_End);
					return;
				}
				++RoarCount;
			}
		});
	ShipState.SetUpdateFunction(PirateBossState::Ship_Phase2_Transforming_End, [](float) {});
	ShipState.SetUpdateFunction(PirateBossState::Ship_Phase2_Idle, std::bind(&ACaptainBrineybeardPhase2::Ship_Idle, this, std::placeholders::_1));
	ShipState.SetUpdateFunction(PirateBossState::Ship_phase2_LazarAtt_Begin, [](float) {});
	ShipState.SetUpdateFunction(PirateBossState::Ship_phase2_LazarAtt_Charging, [this](float)
		{
			if (true == ShipRenderer->IsCurAnimationEnd())
			{
				if (ChargingTime <= ChargingCount)
				{
					ChargingCount = 0;
					
					ShipState.ChangeState(PirateBossState::Ship_phase2_LazarAtt_ChargingEnd);
					return;
				}
				++ChargingCount;
			}
		});
	ShipState.SetUpdateFunction(PirateBossState::Ship_phase2_LazarAtt_ChargingEnd, [](float) {});
	ShipState.SetUpdateFunction(PirateBossState::Ship_phase2_LazarAttack, [this](float)
		{
			if (true == ShipRenderer->IsCurAnimationEnd())
			{
				if (LazarAttTime <= LazarAttCount)
				{
					LazarAttCount = 0;

					ShipState.ChangeState(PirateBossState::Ship_phase2_LazarAttack_End);
					return;
				}
				++LazarAttCount;
			}
		});
	ShipState.SetUpdateFunction(PirateBossState::Ship_phase2_LazarAttack_End, [](float) {});
}

void ACaptainBrineybeardPhase2::EndFunctionSet()
{
	ShipState.SetEndFunction(PirateBossState::Ship_Phase2_Idle, [this]()
		{
			JawRenderer->AnimationReset();
			UvulaRenderer->AnimationReset();
			JawRenderer->SetActive(false);
			UvulaRenderer->SetActive(false);
		});
}

void ACaptainBrineybeardPhase2::Ship_Idle(float _DeltaTime)
{
	LazarShootDelay -= _DeltaTime;

	if (0.0f >= LazarShootDelay)
	{
		LazarShootDelay = LazarShootDelayInit;
		ShipState.ChangeState(PirateBossState::Ship_phase2_LazarAtt_Begin);
		return;
	}


	BubbleShootDelay -= _DeltaTime;

	if (0.0f >= BubbleShootDelay)
	{
		BubbleShootDelay = BubbleShootDelayInit;
		UvulaRenderer->ChangeAnimation(PirateBossAniName::Uvula_Shoot);
	}

}