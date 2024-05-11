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
		ShipState.CreateState(PirateBossState::Ship_Phase1_Blink);
		ShipState.CreateState(PirateBossState::Ship_Phase1_CannonShoot);
		ShipState.CreateState(PirateBossState::Ship_Wince);
		ShipState.CreateState(PirateBossState::Ship_Transform_Begin);
	}

	// Pirate
	{
		PirateState.CreateState(PirateBossState::Pirate_Intro);
		PirateState.CreateState(PirateBossState::Pirate_Laugh);
		PirateState.CreateState(PirateBossState::Pirate_Idle);
		PirateState.CreateState(PirateBossState::Pirate_Whistle);
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
		ShipState.SetStartFunction(PirateBossState::Ship_Phase1_Blink, [this]()
			{
				ShipRenderer->ChangeAnimation(PirateBossAniName::Ship_Phase1_Blink);
			});
		ShipState.SetStartFunction(PirateBossState::Ship_Phase1_CannonShoot, [this]()
			{
				UEngineSoundPlayer Sound = UEngineSound::SoundPlay("pirate_boat_cannon_chew.wav");
				Sound.SetVolume(0.5f);

				ShipRenderer->ChangeAnimation(PirateBossAniName::Ship_Phase1_CannonAtt);
			});
		ShipState.SetStartFunction(PirateBossState::Ship_Wince, [this]()
			{
				UEngineSoundPlayer Sound = UEngineSound::SoundPlay("pirate_boat_transform.wav");
				Sound.SetVolume(0.7f);
				
				ShipRenderer->ChangeAnimation(PirateBossAniName::Ship_Phase1_Wince_Begin);
			});
		ShipState.SetStartFunction(PirateBossState::Ship_Transform_Begin, [this]()
			{
				ShipRenderer->ChangeAnimation(PirateBossAniName::Ship_Transform_Begin);
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
				UEngineSoundPlayer Sound = UEngineSound::SoundPlay("pirate_laugh.wav");
				Sound.SetVolume(0.5f);

				Laughing = true;
				PirateRenderer->ChangeAnimation(PirateBossAniName::Pirate_Laugh);
			});
		PirateState.SetStartFunction(PirateBossState::Pirate_Idle, [this]()
			{
				PirateRenderer->ChangeAnimation(PirateBossAniName::Pirate_Idle);
				PirateRenderer->SetPosition(GRendererPos::Pirate_Idle_ReletivePos);
			});
		PirateState.SetStartFunction(PirateBossState::OctopusShoot_Begin, [this]()
			{
				UEngineSound::SoundPlay("pirate_gun_start.wav");
				PirateRenderer->ChangeAnimation(PirateBossAniName::OctopusShoot_Begin);
				PirateRenderer->SetPosition(GRendererPos::Pirate_OctoPusAtt_ReletivePos);
			});
		PirateState.SetStartFunction(PirateBossState::OctopusShoot_Idle, [this]()
			{
				PirateRenderer->ChangeAnimation(PirateBossAniName::OctopusShoot_Idle);

				PirateTopRenderer->ChangeAnimation(PirateBossAniName::OctopusShoot_Idle_Top);
			});
		PirateState.SetStartFunction(PirateBossState::OctopusShoot_Attack, [this]()
			{
				PlayOctoBulletShootSound();

				PirateRenderer->ChangeAnimation(PirateBossAniName::OctopusShoot_Attack);
				PirateTopRenderer->ChangeAnimation(PirateBossAniName::OctopusShoot_Attack_Top);
			});
		PirateState.SetStartFunction(PirateBossState::OctopusShoot_End, [this]()
			{
				UEngineSound::SoundPlay("pirate_gun_end.wav");

				PirateRenderer->ChangeAnimation(PirateBossAniName::OctopusShoot_End);
				PirateTopRenderer->ChangeAnimation(PirateBossAniName::OctopusShoot_End_Top);
			});
		PirateState.SetStartFunction(PirateBossState::Pirate_Whistle, [this]()
			{
				PirateRenderer->ChangeAnimation(PirateBossAniName::Pirate_Whistle);
				PirateRenderer->SetPosition(GRendererPos::Pirate_Whistle_RelativePos);
			});

	}
}

void ACaptainBrineybeardPhase1::UpdateFunctionSet()
{
	// Ship State
	{
		ShipState.SetUpdateFunction(PirateBossState::Ship_Phase1_Idle, std::bind(&ACaptainBrineybeardPhase1::Ship_Idle, this, std::placeholders::_1));
		ShipState.SetUpdateFunction(PirateBossState::Ship_Phase1_Blink, std::bind(&ACaptainBrineybeardPhase1::Ship_Blink, this, std::placeholders::_1));
		ShipState.SetUpdateFunction(PirateBossState::Ship_Phase1_CannonShoot, std::bind(&ACaptainBrineybeardPhase1::Ship_CannonShoot, this, std::placeholders::_1));
		ShipState.SetUpdateFunction(PirateBossState::Ship_Wince, std::bind(&ACaptainBrineybeardPhase1::Ship_Wince, this, std::placeholders::_1));
		ShipState.SetUpdateFunction(PirateBossState::Ship_Transform_Begin, [](float) {});
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
		PirateState.SetUpdateFunction(PirateBossState::Pirate_Whistle, [](float) {});
	}
}

void ACaptainBrineybeardPhase1::EndFunctionSet()
{

}

void ACaptainBrineybeardPhase1::Ship_Idle(float _DeltaTime)
{
	if (static_cast<int>(EPirateBossPattern::ShootCanonBall) == PatternNum
		|| static_cast<int>(EPirateBossPattern::Phase2) == PatternNum
		)
	{
		Dbg_PatternSwitchDelay -= _DeltaTime;

		if (0.0f >= Dbg_PatternSwitchDelay)
		{
			Dbg_ChangeState();
		}
		return;
	}

	if (0 >= GetHp())
	{
		ShipState.ChangeState(PirateBossState::Ship_Wince);
		return;
	}

	BlinkDelay -= _DeltaTime;

	if (0.0f >= BlinkDelay)
	{
		BlinkDelay = BlinkDelayInit + BlinkDelay;

		ShipState.ChangeState(PirateBossState::Ship_Phase1_Blink);
		return;
	}

	if (ShipAttackStartHp >= GetHp())
	{
		CannonShootDelay -= _DeltaTime;

		if (0.0f >= CannonShootDelay)
		{
			CannonShootDelay = CannonShootDelayInit + CannonShootDelay;

			ShipState.ChangeState(PirateBossState::Ship_Phase1_CannonShoot);
			return;
		}
	}

	MoveUpAndDown(_DeltaTime);
}

void ACaptainBrineybeardPhase1::Pirate_Idle(float _DeltaTime)
{
	if (static_cast<int>(EPirateBossPattern::OctopusShootAtt) == PatternNum)
	{
		Dbg_PatternSwitchDelay -= _DeltaTime;

		if (0.0f >= Dbg_PatternSwitchDelay)
		{
			Dbg_ChangeState();
		}
		return;
	}

	if (0 >= GetHp())
	{
		return;
	}

	PickOctopusDelay -= _DeltaTime;

	if (0.0f >= PickOctopusDelay && true == PirateRenderer->IsCurAnimationEnd())
	{
		PickOctopusDelay = PickOctopusDelayInit;

		PirateState.ChangeState(PirateBossState::OctopusShoot_Begin);
		return;
	}

	WhistleDelay -= _DeltaTime;

	if (0.0f >= WhistleDelay && true == PirateRenderer->IsCurAnimationEnd())
	{
		WhistleDelay = WhistleDelayInit;

		PirateState.ChangeState(PirateBossState::Pirate_Whistle);
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

void ACaptainBrineybeardPhase1::Ship_CannonShoot(float _DeltaTime)
{
	MoveUpAndDown(_DeltaTime);
}

void ACaptainBrineybeardPhase1::Ship_Blink(float _DeltaTime)
{
	MoveUpAndDown(_DeltaTime);
}

void ACaptainBrineybeardPhase1::Ship_Wince(float _DeltaTime)
{
	if (true == ShipRenderer->IsCurAnimationEnd())
	{
		if (WinceTime <= WinceCount)
		{
			ShipState.ChangeState(PirateBossState::Ship_Transform_Begin);
			return;
		}

		++WinceCount;
	}
}