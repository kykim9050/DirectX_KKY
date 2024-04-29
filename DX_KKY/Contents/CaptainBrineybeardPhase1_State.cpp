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
		PirateState.CreateState(PirateBossState::Pirate_Idle);
		PirateState.CreateState(PirateBossState::OctopusShoot_Begin);
		PirateState.CreateState(PirateBossState::OctopusShoot_Idle);
		PirateState.CreateState(PirateBossState::OctopusShoot_Attack);
		PirateState.CreateState(PirateBossState::OctopusShoot_End);
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
				Laughing = true;
				PirateRenderer->ChangeAnimation(PirateBossAniName::Pirate_Laugh);
			});
		PirateState.SetStartFunction(PirateBossState::Pirate_Idle, [this]()
			{
				PirateRenderer->SetPosition(GRendererPos::Pirate_Idle_ReletivePos);
				PirateRenderer->ChangeAnimation(PirateBossAniName::Pirate_Idle);
			});
		PirateState.SetStartFunction(PirateBossState::OctopusShoot_Begin, [this]()
			{
				PirateRenderer->SetPosition(GRendererPos::Pirate_OctoPusAtt_ReletivePos);
				PirateRenderer->ChangeAnimation(PirateBossAniName::OctopusShoot_Begin);
			});
		PirateState.SetStartFunction(PirateBossState::OctopusShoot_Idle, [this]()
			{
				PirateRenderer->ChangeAnimation(PirateBossAniName::OctopusShoot_Idle);

				PirateTopRenderer->ChangeAnimation(PirateBossAniName::OctopusShoot_Idle_Top);
			});
		PirateState.SetStartFunction(PirateBossState::OctopusShoot_Attack, [this]()
			{
				PirateRenderer->ChangeAnimation(PirateBossAniName::OctopusShoot_Attack);

				PirateTopRenderer->ChangeAnimation(PirateBossAniName::OctopusShoot_Attack_Top);
			});
		PirateState.SetStartFunction(PirateBossState::OctopusShoot_End, [this]()
			{
				PirateRenderer->ChangeAnimation(PirateBossAniName::OctopusShoot_End);

				PirateTopRenderer->ChangeAnimation(PirateBossAniName::OctopusShoot_End_Top);
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
				if (true == Laughing && true == PirateRenderer->IsCurAnimationEnd())
				{
					if (LaughCount >= LaughNum)
					{
						Laughing = false;
						LaughCount = 1;
						PirateRenderer->ChangeAnimation(PirateBossAniName::Pirate_StopLaugh);
						return;
					}

					++LaughCount;
				}
			});
		PirateState.SetUpdateFunction(PirateBossState::Pirate_Idle, std::bind(&ACaptainBrineybeardPhase1::Pirate_Idle, this, std::placeholders::_1));
		PirateState.SetUpdateFunction(PirateBossState::OctopusShoot_Begin, [](float) {});
		PirateState.SetUpdateFunction(PirateBossState::OctopusShoot_Idle, std::bind(&ACaptainBrineybeardPhase1::Pirate_OctoAtt_Idle, this, std::placeholders::_1));
		PirateState.SetUpdateFunction(PirateBossState::OctopusShoot_Attack, [](float) {});
		PirateState.SetUpdateFunction(PirateBossState::OctopusShoot_End, [](float) {});
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

void ACaptainBrineybeardPhase1::Pirate_Idle(float _DeltaTime)
{
	PickOctopusDelay -= _DeltaTime;

	if (0.0f >= PickOctopusDelay && 8 == PirateRenderer->GetCurAnimationFrame())
	{
		PickOctopusDelay = PickOctopusDelayInit;

		PirateState.ChangeState(PirateBossState::OctopusShoot_Begin);
		return;
	}
}

void ACaptainBrineybeardPhase1::Pirate_OctoAtt_Idle(float _DeltaTime)
{
	ShootDelay -= _DeltaTime;

	if (ShootNum < ShootCount && true == PirateRenderer->IsCurAnimationEnd())
	{
		ShootCount = 1;
		PirateState.ChangeState(PirateBossState::OctopusShoot_End);
		return;
	}

	if (0.0f >= ShootDelay)
	{
		ShootDelay = ShootDelayInit;
		++ShootCount;
		PirateState.ChangeState(PirateBossState::OctopusShoot_Attack);
		return;
	}
}