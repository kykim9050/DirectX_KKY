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
		State.CreateState("Aim_Up");
		State.CreateState("Aim_DiagonalUp");
		State.CreateState("Aim_Straight");
		State.CreateState("Aim_DiagonalDown");
		State.CreateState("Aim_Down");

		State.CreateState("IdleShoot_Straight");
		State.CreateState("IdleShoot_Up");

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
		State.SetUpdateFunction("Aim_Up", std::bind(&APlayer::Aim_Up, this, std::placeholders::_1));
		State.SetUpdateFunction("Aim_DiagonalUp", std::bind(&APlayer::Aim_DiagonalUp, this, std::placeholders::_1));
		State.SetUpdateFunction("Aim_Straight", std::bind(&APlayer::Aim_Straight, this, std::placeholders::_1));
		State.SetUpdateFunction("Aim_DiagonalDown", std::bind(&APlayer::Aim_DiagonalDown, this, std::placeholders::_1));
		State.SetUpdateFunction("Aim_Down", std::bind(&APlayer::Aim_Down, this, std::placeholders::_1));
		State.SetUpdateFunction("IdleShoot_Straight", std::bind(&APlayer::IdleShoot_Straight, this, std::placeholders::_1));
		State.SetUpdateFunction("IdleShoot_Up", std::bind(&APlayer::IdleShoot_Up, this, std::placeholders::_1));


		State.SetStartFunction("Idle", [this]
			{
				DirCheck();
				SetAvailableParry(true);
				SetAvailableAddJumpVec(false);
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
				SetAvailableAddJumpVec(false);
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
				SetAvailableAddJumpVec(false);
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
				SetAvailableAddJumpVec(false);
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
				SetAvailableAddJumpVec(false);
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
		State.SetStartFunction("Aim_Up", [this]
			{
				DirCheck();
				Renderer->ChangeAnimation("Player_Aim_Up");
				AnimationDirSet(Renderer, Dir);
			}
		);
		State.SetStartFunction("Aim_DiagonalUp", [this]
			{
				DirCheck();
				Renderer->ChangeAnimation("Player_Aim_DiagonalUp");
				AnimationDirSet(Renderer, Dir);
			}
		);
		State.SetStartFunction("Aim_Straight", [this]
			{
				DirCheck();
				Renderer->ChangeAnimation("Player_Aim_Straight");
				AnimationDirSet(Renderer, Dir);
			}
		);
		State.SetStartFunction("Aim_DiagonalDown", [this]
			{
				DirCheck();
				Renderer->ChangeAnimation("Player_Aim_DiagonalDown");
				AnimationDirSet(Renderer, Dir);
			}
		);
		State.SetStartFunction("Aim_Down", [this]
			{
				DirCheck();
				Renderer->ChangeAnimation("Player_Aim_Down");
				AnimationDirSet(Renderer, Dir);
			}
		);
		State.SetStartFunction("IdleShoot_Straight", [this]
			{
				DirCheck();
				Renderer->ChangeAnimation("Player_Shoot_Straight");
				AnimationDirSet(Renderer, Dir);
			}
		);
		State.SetStartFunction("IdleShoot_Up", [this]
			{
				DirCheck();
				Renderer->ChangeAnimation("Player_Shoot_Up");
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

	if (true == IsPress('X'))
	{
		if (true == IsPress(VK_UP))
		{
			State.ChangeState("IdleShoot_Up");
			return;
		}

		State.ChangeState("IdleShoot_Straight");
		return;
	}

	if (true == IsPress('C'))
	{
		State.ChangeState("Aim_Straight");
		return;
	}

	if (true == IsPress(VK_UP))
	{
		State.ChangeState("Aim_Up");
		return;
	}

	ResultMovementUpdate(_DeltaTime);
}

void APlayer::Run(float _DeltaTime)
{
	if (true == IsFree(VK_RIGHT) && true == IsFree(VK_LEFT))
	{
		if (true == IsPress(VK_UP))
		{
			State.ChangeState("Aim_Up");
			return;
		}

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


	if (true == IsPress(VK_RIGHT) || true == IsPress(VK_LEFT))
	{
		if (true == IsPress(VK_UP) && true == IsDown('C'))
		{
			State.ChangeState("Aim_DiagonalUp");
			return;
		}

		if (true == IsDown('C'))
		{
			State.ChangeState("Aim_Straight");
			return;
		}
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

	SetAvailableAddJumpVec(false);
	if (true == IsPress('Z') && 0.2f >= GetPressTime('Z'))
	{
		SetAvailableAddJumpVec(true);
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

	AddGravityVec(0.4f, _DeltaTime);
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

void APlayer::Aim_Up(float _DeltaTime)
{
	// Aim 끼리 상태 변화
	if (true == IsPress('C'))
	{
		if (true == IsPress(VK_UP) && (true == IsDown(VK_RIGHT) || true == IsDown(VK_LEFT)))
		{
			State.ChangeState("Aim_DiagonalUp");
			return;
		}

		if (true == IsUp(VK_UP))
		{
			State.ChangeState("Aim_Straight");
			return;
		}
	}

	if (true == IsUp(VK_UP))
	{
		State.ChangeState("Idle");
		return;
	}

	if (true == IsPress(VK_RIGHT) || true == IsPress(VK_LEFT))
	{
		State.ChangeState("Run");
		return;
	}

	//if (true == IsDown('X'))
	//{
	//	State.ChangeState("IdleShoot_Up");
	//	return;
	//}
}

void APlayer::Aim_DiagonalUp(float _DeltaTime)
{
	// Aim 끼리 상태 변화
	if (true == IsPress('C'))
	{
		if (true == IsUp(VK_UP))
		{
			State.ChangeState("Aim_Straight");
			return;
		}

		if (true == IsPress(VK_UP) && (true == IsUp(VK_RIGHT) || true == IsUp(VK_LEFT)))
		{
			State.ChangeState("Aim_Up");
			return;
		}
	}

	if (true == IsPress(VK_RIGHT) || true == IsPress(VK_LEFT))
	{
		if (true == IsPress(VK_UP) && true == IsUp('C'))
		{
			State.ChangeState("Run");
			return;
		}
	}
}

void APlayer::Aim_Straight(float _DeltaTime)
{
	// Aim 끼리 상태 변화
	if (true == IsPress('C'))
	{
		if (true == IsDown(VK_DOWN) && (true == IsPress(VK_RIGHT) || true == IsPress(VK_LEFT)))
		{
			State.ChangeState("Aim_DiagonalDown");
			return;
		}

		if (true == IsDown(VK_UP) && (true == IsPress(VK_RIGHT) || true == IsPress(VK_LEFT)))
		{
			State.ChangeState("Aim_DiagonalUp");
			return;
		}

		if (true == IsDown(VK_DOWN))
		{
			State.ChangeState("Aim_Down");
			return;
		}

		if (true == IsDown(VK_UP))
		{
			State.ChangeState("Aim_Up");
			return;
		}
	}

	if (true == IsPress(VK_RIGHT) || true == IsPress(VK_LEFT))
	{
		if (true == IsUp('C'))
		{
			State.ChangeState("Run");
			return;
		}
	}

	if (true == IsUp('C'))
	{
		State.ChangeState("Idle");
		return;
	}

	//if (true == IsDown('X'))
	//{
	//	State.ChangeState("IdleShoot_Straight");
	//	return;
	//}

	//if (true == IsPress('C') && true == IsDown(VK_UP))
	//{
	//	State.ChangeState("Aim_Up");
	//	return;
	//}

	//if (true == IsPress(VK_LEFT) || true == IsPress(VK_RIGHT))
	//{
	//	DirCheck();
	//	AnimationDirSet(Renderer, Dir);
	//}
}

void APlayer::Aim_DiagonalDown(float _DeltaTime)
{
	// Aim 끼리 상태 변화
	if (true == IsPress('C'))
	{
		if (true == IsUp(VK_DOWN) && (true == IsPress(VK_RIGHT) || true == IsPress(VK_LEFT)))
		{
			State.ChangeState("Aim_Straight");
			return;
		}

		if (true == IsPress(VK_DOWN) && (true == IsUp(VK_RIGHT) || true == IsUp(VK_LEFT)))
		{
			State.ChangeState("Aim_Down");
			return;
		}
	}
}

void APlayer::Aim_Down(float _DeltaTime)
{
	// Aim 끼리 상태 변화
	if (true == IsPress('C'))
	{
		if (true == IsUp(VK_DOWN))
		{
			State.ChangeState("Aim_Straight");
			return;
		}

		if (true == IsPress(VK_DOWN) && (true == IsDown(VK_RIGHT) || true == IsDown(VK_LEFT)))
		{
			State.ChangeState("Aim_DiagonalDown");
			return;
		}
	}
}

void APlayer::IdleShoot_Straight(float _DeltaTime)
{
	if (true == IsUp('X'))
	{
		if (true == IsPress('C'))
		{
			State.ChangeState("Aim_Straight");
			return;
		}

		State.ChangeState("Idle");
		return;
	}

	if (true == IsPress(VK_UP))
	{
		State.ChangeState("IdleShoot_Up");
		return;
	}

	if (true == IsPress(VK_LEFT) || true == IsPress(VK_RIGHT))
	{
		DirCheck();
		AnimationDirSet(Renderer, Dir);
	}
}

void APlayer::IdleShoot_Up(float _DeltaTime)
{
	if (true == IsUp('X'))
	{
		State.ChangeState("Idle");
		return;
	}

	if (true == IsUp(VK_UP))
	{
		State.ChangeState("IdleShoot_Straight");
		return;
	}
}