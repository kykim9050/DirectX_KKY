#include "PreCompile.h"

#include "Player.h"
#include <EngineCore/SpriteRenderer.h>
#include "MoveUnit.h"

void APlayer::StateInit()
{
	{
		State.CreateState("Idle");
		State.CreateState("Run");
		State.CreateState("Jump");
		State.CreateState("DuckIdle");
		State.CreateState("Duck");
		State.CreateState("Parry");
		State.CreateState("AfterParry");
		State.CreateState("Dash");
		State.CreateState("DashAir");
		State.CreateState("AfterDashAir");

		State.SetUpdateFunction("Idle", std::bind(&APlayer::Idle, this, std::placeholders::_1));
		State.SetUpdateFunction("Run", std::bind(&APlayer::Run, this, std::placeholders::_1));
		State.SetUpdateFunction("Jump", std::bind(&APlayer::Jump, this, std::placeholders::_1));
		State.SetUpdateFunction("DuckIdle", std::bind(&APlayer::DuckIdle, this, std::placeholders::_1));
		State.SetUpdateFunction("Duck", std::bind(&APlayer::Duck, this, std::placeholders::_1));
		State.SetUpdateFunction("Parry", std::bind(&APlayer::Parry, this, std::placeholders::_1));
		State.SetUpdateFunction("AfterParry", std::bind(&APlayer::AfterParry, this, std::placeholders::_1));
		State.SetUpdateFunction("Dash", std::bind(&APlayer::Dash, this, std::placeholders::_1));
		State.SetUpdateFunction("DashAir", std::bind(&APlayer::DashAir, this, std::placeholders::_1));
		State.SetUpdateFunction("AfterDashAir", std::bind(&APlayer::AfterDashAir, this, std::placeholders::_1));


		State.SetStartFunction("Idle", [this]
			{
				DirCheck();
				SetAvailableParry(true);
				SetSpeedVec(float4::Zero);
				SetJumpVec(float4::Zero);
				Renderer->ChangeAnimation("Player_Idle");
				AnimationDirSet(Renderer, Dir);
			}
		);
		State.SetStartFunction("Run", [this]
			{
				DirCheck();
				SetAvailableParry(true);
				Renderer->ChangeAnimation("Player_Run");
				AnimationDirSet(Renderer, Dir);
			}
		);
		State.SetStartFunction("Jump", [this]
			{
				DirCheck();
				AddActorLocation(float4::Up * 10);
				SetJumpVec(float4::Up * GetJumpVal());
				Renderer->ChangeAnimation("Player_Jump");
				AnimationDirSet(Renderer, Dir);
			}
		);
		State.SetStartFunction("Duck", [this]
			{
				DirCheck();
				SetAvailableParry(true);
				SetSpeedVec(float4::Zero);
				SetJumpVec(float4::Zero);
				Renderer->ChangeAnimation("Player_Duck");
				AnimationDirSet(Renderer, Dir);
			}
		);
		State.SetStartFunction("DuckIdle", [this]
			{
				DirCheck();
				SetAvailableParry(true);
				SetSpeedVec(float4::Zero);
				SetJumpVec(float4::Zero);
				Renderer->ChangeAnimation("Player_DuckIdle");
				AnimationDirSet(Renderer, Dir);
			}
		);
		State.SetStartFunction("Parry", [this]
			{
				DirCheck();
				SetAvailableParry(false);
				Renderer->ChangeAnimation("Player_Parry");
				AnimationDirSet(Renderer, Dir);
			}
		);
		State.SetStartFunction("AfterParry", [this]
			{
				DirCheck();
				SetJumpVec(GetPrevJumpVec());
				Renderer->ChangeAnimation("Player_Jump");
				AnimationDirSet(Renderer, Dir);
			}
		);
		State.SetStartFunction("Dash", [this]
			{
				DirCheck();
				Renderer->ChangeAnimation("Player_Dash");
				AnimationDirSet(Renderer, Dir);
			}
		);
		State.SetStartFunction("DashAir", [this]
			{
				DirCheck();
				Renderer->ChangeAnimation("Player_Dash_Air");
				AnimationDirSet(Renderer, Dir);
			}
		);
		State.SetStartFunction("AfterDashAir", [this]
			{
				DirCheck();
				SetJumpVec(GetPrevJumpVec());
				SetGravityVec(GetPrevGravityVec());
				Renderer->ChangeAnimation("Player_Jump");
				AnimationDirSet(Renderer, Dir);
			}
		);
	}

	State.ChangeState("Idle");
}

bool APlayer::DirCheck()
{
	EActorDir ActorDir = Dir;

	if (true == IsPress(VK_LEFT) && UEngineInput::IsFree(VK_RIGHT))
	{
		ActorDir = EActorDir::Left;
	}

	if (true == IsPress(VK_RIGHT) && UEngineInput::IsFree(VK_LEFT))
	{
		ActorDir = EActorDir::Right;
	}

	if (ActorDir != Dir)
	{
		Dir = ActorDir;
		return false;
	}

	return true;
}

void APlayer::Idle(float _DeltaTime)
{
	if (true == IsPress(VK_LEFT) || true == IsPress(VK_RIGHT))
	{
		State.ChangeState("Run");
		return;
	}

	if (true == IsDown('Z'))
	{
		State.ChangeState("Jump");
		return;
	}

	if (true == IsDown(VK_DOWN))
	{
		State.ChangeState("Duck");
		return;
	}

	if (true == IsDown(VK_SHIFT))
	{
		SetPrevState(State.GetCurStateName());
		State.ChangeState("Dash");
		return;
	}

	ResultMovementUpdate(_DeltaTime);
}

void APlayer::Run(float _DeltaTime)
{
	if (true == IsFree(VK_RIGHT) && true == IsFree(VK_LEFT))
	{
		State.ChangeState("Idle");
		return;
	}

	if (true == IsDown('Z'))
	{
		State.ChangeState("Jump");
		return;
	}

	if (true == IsDown(VK_DOWN))
	{
		State.ChangeState("Duck");
		return;
	}

	if (true == IsDown(VK_SHIFT))
	{
		SetPrevState(State.GetCurStateName());
		State.ChangeState("Dash");
		return;
	}

	if (false == DirCheck())
	{
		AnimationDirSet(Renderer, Dir);
	}

	SetSpeedVec(MoveDir(Dir) * GetRunSpeed());
	ResultMovementUpdate(_DeltaTime);
}

void APlayer::Jump(float _DeltaTime)
{
	float4 Pos = GetActorLocation();
	Pos.Y = -Pos.Y;

	if (true == BottomCheck(Pos, Color8Bit::Black))
	{

		if (true == IsPress(VK_DOWN))
		{
			State.ChangeState("Duck");
			return;
		}

		State.ChangeState("Idle");
		return;
	}

	if (true == GetAvailableParry() && true == IsDown('Z'))
	{
		State.ChangeState("Parry");
		return;
	}
	else if (true == IsPress('Z') && 0.2f >= GetPressTime('Z'))
	{
		SetAvailableAddJumpVec(true);
	}
	else
	{
		SetAvailableAddJumpVec(false);
	}

	if (true == IsDown(VK_SHIFT))
	{
		State.ChangeState("DashAir");
		return;
	}

	if (true == IsPress(VK_LEFT) || true == IsPress(VK_RIGHT))
	{
		DirCheck();
		SetSpeedVec(MoveDir(Dir) * GetRunSpeed());
		AnimationDirSet(Renderer, Dir);
	}

	if (true == IsFree(VK_LEFT) && true == IsFree(VK_RIGHT))
	{
		SetSpeedVec(float4::Zero);
	}

	ResultMovementUpdate(_DeltaTime);
}

void APlayer::DuckIdle(float _DeltaTime)
{
	if (true == IsUp(VK_DOWN))
	{
		State.ChangeState("Idle");
		return;
	}

	if (true == IsDown(VK_LEFT) || true == IsDown(VK_RIGHT))
	{
		if (false == DirCheck())
		{
			State.ChangeState("DuckIdle");
			return;
		}
	}

	if (true == IsDown('Z'))
	{
		State.ChangeState("Jump");
		return;
	}

	if (true == IsDown(VK_SHIFT))
	{
		SetPrevState(State.GetCurStateName());
		State.ChangeState("Dash");
		return;
	}

	ResultMovementUpdate(_DeltaTime);
}

void APlayer::Duck(float _DeltaTime)
{
	if (true == IsUp(VK_DOWN))
	{
		State.ChangeState("Idle");
		return;
	}

	if (true == IsDown(VK_LEFT) || true == IsDown(VK_RIGHT))
	{
		if (false == DirCheck())
		{
			State.ChangeState("DuckIdle");
			return;
		}
	}

	if (true == IsDown('Z'))
	{
		State.ChangeState("Jump");
		return;
	}

	if (true == IsDown(VK_SHIFT))
	{
		SetPrevState(State.GetCurStateName());
		State.ChangeState("Dash");
		return;
	}

	ResultMovementUpdate(_DeltaTime);
}

void APlayer::Parry(float _DeltaTime)
{
	float4 Pos = GetActorLocation();
	Pos.Y = -Pos.Y;

	if (true == BottomCheck(Pos, Color8Bit::Black))
	{
		if (true == IsPress(VK_DOWN))
		{
			State.ChangeState("Duck");
			return;
		}

		State.ChangeState("Idle");
		return;
	}

	if (true == IsDown(VK_SHIFT))
	{
		State.ChangeState("DashAir");
		return;
	}

	if (true == IsPress(VK_LEFT))
	{
		SetSpeedVec(float4::Left * GetRunSpeed());
		Renderer->SetDir(EEngineDir::Left);
	}
	if (true == IsPress(VK_RIGHT))
	{
		SetSpeedVec(float4::Right * GetRunSpeed());
		Renderer->SetDir(EEngineDir::Right);
	}

	if (true == IsFree(VK_LEFT) && true == IsFree(VK_RIGHT))
	{
		SetSpeedVec(float4::Zero);
	}

	ResultMovementUpdate(_DeltaTime);
}

void APlayer::AfterParry(float _DeltaTime)
{
	float4 Pos = GetActorLocation();
	Pos.Y = -Pos.Y;

	if (true == BottomCheck(Pos, Color8Bit::Black))
	{
		if (true == IsPress(VK_DOWN))
		{
			DirCheck();
			State.ChangeState("Duck");
			return;
		}

		DirCheck();
		State.ChangeState("Idle");
		return;
	}

	if (true == IsDown(VK_SHIFT))
	{
		State.ChangeState("DashAir");
		return;
	}

	if (true == IsPress(VK_LEFT))
	{
		SetSpeedVec(float4::Left * GetRunSpeed());
		Renderer->SetDir(EEngineDir::Left);
	}
	if (true == IsPress(VK_RIGHT))
	{
		SetSpeedVec(float4::Right * GetRunSpeed());
		Renderer->SetDir(EEngineDir::Right);
	}

	if (true == IsFree(VK_LEFT) && true == IsFree(VK_RIGHT))
	{
		SetSpeedVec(float4::Zero);
	}

	ResultMovementUpdate(_DeltaTime);
}

void APlayer::Dash(float _DeltaTime)
{
	AddActorLocation(MoveDir(Dir) * GetDashSpeed() * _DeltaTime);
}

void APlayer::DashAir(float _DeltaTime)
{
	if (true == GetAvailableParry() && true == IsDown('Z'))
	{
		State.ChangeState("Parry");
		return;
	}

	AddGravityVec(0.5, _DeltaTime);
	AddActorLocation(MoveDir(Dir) * GetDashSpeed() * _DeltaTime);
}

void APlayer::AfterDashAir(float _DeltaTime)
{
	float4 Pos = GetActorLocation();
	Pos.Y = -Pos.Y;

	if (true == BottomCheck(Pos, Color8Bit::Black))
	{

		if (true == IsPress(VK_DOWN))
		{
			State.ChangeState("Duck");
			return;
		}

		State.ChangeState("Idle");
		return;
	}

	if (true == GetAvailableParry() && true == IsDown('Z'))
	{
		State.ChangeState("Parry");
		return;
	}

	if (true == IsPress(VK_LEFT) || true == IsPress(VK_RIGHT))
	{
		DirCheck();
		SetSpeedVec(MoveDir(Dir) * GetRunSpeed());
		AnimationDirSet(Renderer, Dir);
	}

	if (true == IsFree(VK_LEFT) && true == IsFree(VK_RIGHT))
	{
		SetSpeedVec(float4::Zero);
	}

	ResultMovementUpdate(_DeltaTime);
}