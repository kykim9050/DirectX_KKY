#include "PreCompile.h"

#include "Player.h"
#include <EngineCore/SpriteRenderer.h>
#include "MoveUnit.h"

void APlayer::StateInit()
{
	{
		//State.CreateState("Idle_Left");
		//State.CreateState("Idle_Right");
		State.CreateState("Idle");
		//State.CreateState("Run_Left");
		//State.CreateState("Run_Right");
		State.CreateState("Run");
		//State.CreateState("Jump_Left");
		//State.CreateState("Jump_Right");
		State.CreateState("Jump");
		//State.CreateState("DuckIdle_Left");
		//State.CreateState("DuckIdle_Right");
		State.CreateState("DuckIdle");
		//State.CreateState("Duck_Left");
		//State.CreateState("Duck_Right");
		State.CreateState("Duck");
		State.CreateState("Parry");
		State.CreateState("AfterParry");


		//State.SetUpdateFunction("Idle_Left", std::bind(&APlayer::IdleLeft, this, std::placeholders::_1));
		//State.SetUpdateFunction("Idle_Right", std::bind(&APlayer::IdleRight, this, std::placeholders::_1));
		State.SetUpdateFunction("Idle", std::bind(&APlayer::Idle, this, std::placeholders::_1));
		//State.SetUpdateFunction("Run_Left", std::bind(&APlayer::RunLeft, this, std::placeholders::_1));
		//State.SetUpdateFunction("Run_Right", std::bind(&APlayer::RunRight, this, std::placeholders::_1));
		State.SetUpdateFunction("Run", std::bind(&APlayer::Run, this, std::placeholders::_1));
		//State.SetUpdateFunction("Jump_Left", std::bind(&APlayer::JumpLeft, this, std::placeholders::_1));
		//State.SetUpdateFunction("Jump_Right", std::bind(&APlayer::JumpRight, this, std::placeholders::_1));
		State.SetUpdateFunction("Jump", std::bind(&APlayer::Jump, this, std::placeholders::_1));
		//State.SetUpdateFunction("DuckIdle_Left", std::bind(&APlayer::DuckIdleLeft, this, std::placeholders::_1));
		//State.SetUpdateFunction("DuckIdle_Right", std::bind(&APlayer::DuckIdleRight, this, std::placeholders::_1));
		State.SetUpdateFunction("DuckIdle", std::bind(&APlayer::DuckIdle, this, std::placeholders::_1));
		//State.SetUpdateFunction("Duck_Left", std::bind(&APlayer::DuckLeft, this, std::placeholders::_1));
		//State.SetUpdateFunction("Duck_Right", std::bind(&APlayer::DuckRight, this, std::placeholders::_1));
		State.SetUpdateFunction("Duck", std::bind(&APlayer::Duck, this, std::placeholders::_1));
		State.SetUpdateFunction("Parry", std::bind(&APlayer::Parry, this, std::placeholders::_1));
		State.SetUpdateFunction("AfterParry", std::bind(&APlayer::AfterParry, this, std::placeholders::_1));


		//State.SetStartFunction("Idle_Left", [this]
		//	{
		//		DirCheck();
		//		SetAvailableParry(true);
		//		SetSpeedVec(float4::Zero);
		//		SetJumpVec(float4::Zero);
		//		Renderer->ChangeAnimation("Player_Idle");
		//		Renderer->SetDir(EEngineDir::Left);
		//	}
		//);
		//State.SetStartFunction("Idle_Right", [this]
		//	{
		//		DirCheck();
		//		SetAvailableParry(true);
		//		SetSpeedVec(float4::Zero);
		//		SetJumpVec(float4::Zero);
		//		Renderer->ChangeAnimation("Player_Idle");
		//		Renderer->SetDir(EEngineDir::Right);
		//	}
		//);
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
		//State.SetStartFunction("Run_Left", [this]
		//	{
		//		DirCheck();
		//		SetAvailableParry(true);
		//		Renderer->ChangeAnimation("Player_Run");
		//		Renderer->SetDir(EEngineDir::Left);
		//	}
		//);
		//State.SetStartFunction("Run_Right", [this]
		//	{
		//		DirCheck();
		//		SetAvailableParry(true);
		//		Renderer->ChangeAnimation("Player_Run");
		//		Renderer->SetDir(EEngineDir::Right);
		//	}
		//);
		State.SetStartFunction("Run", [this]
			{
				DirCheck();
				SetAvailableParry(true);
				Renderer->ChangeAnimation("Player_Run");
				AnimationDirSet(Renderer, Dir);
			}
		);
		//State.SetStartFunction("Jump_Left", [this]
		//	{
		//		DirCheck();
		//		AddActorLocation(float4::Up * 10);
		//		SetJumpVec(float4::Up * GetJumpVal());
		//		Renderer->ChangeAnimation("Player_Jump");
		//		Renderer->SetDir(EEngineDir::Left);
		//	}
		//);
		//State.SetStartFunction("Jump_Right", [this]
		//	{
		//		DirCheck();
		//		AddActorLocation(float4::Up * 10);
		//		SetJumpVec(float4::Up * GetJumpVal());
		//		Renderer->ChangeAnimation("Player_Jump");
		//		Renderer->SetDir(EEngineDir::Right);
		//	}
		//);
		State.SetStartFunction("Jump", [this]
			{
				DirCheck();
				AddActorLocation(float4::Up * 10);
				SetJumpVec(float4::Up * GetJumpVal());
				Renderer->ChangeAnimation("Player_Jump");
				AnimationDirSet(Renderer, Dir);
			}
		);
		//State.SetStartFunction("Duck_Left", [this]
		//	{
		//		DirCheck();
		//		SetAvailableParry(true);
		//		SetSpeedVec(float4::Zero);
		//		SetJumpVec(float4::Zero);
		//		Renderer->ChangeAnimation("Player_Duck");
		//		Renderer->SetDir(EEngineDir::Left);
		//	}
		//);
		//State.SetStartFunction("Duck_Right", [this]
		//	{
		//		DirCheck();
		//		SetAvailableParry(true);
		//		SetSpeedVec(float4::Zero);
		//		SetJumpVec(float4::Zero);
		//		Renderer->ChangeAnimation("Player_Duck");
		//		Renderer->SetDir(EEngineDir::Right);
		//	}
		//);
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
		//State.SetStartFunction("DuckIdle_Left", [this]
		//	{
		//		DirCheck();
		//		SetAvailableParry(true);
		//		SetSpeedVec(float4::Zero);
		//		SetJumpVec(float4::Zero);
		//		Renderer->ChangeAnimation("Player_DuckIdle");
		//		Renderer->SetDir(EEngineDir::Left);
		//	}
		//);
		//State.SetStartFunction("DuckIdle_Right", [this]
		//	{
		//		DirCheck();
		//		SetAvailableParry(true);
		//		SetSpeedVec(float4::Zero);
		//		SetJumpVec(float4::Zero);
		//		Renderer->ChangeAnimation("Player_DuckIdle");
		//		Renderer->SetDir(EEngineDir::Right);
		//	}
		//);
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

//void APlayer::IdleLeft(float _DeltaTime)
//{
//	if (true == IsPress(VK_LEFT))
//	{
//		State.ChangeState("Run_Left");
//		return;
//	}
//
//	if (true == IsPress(VK_RIGHT))
//	{
//		State.ChangeState("Run_Right");
//		return;
//	}
//
//	if (true == IsDown('Z'))
//	{
//		State.ChangeState("Jump_Left");
//		return;
//	}
//
//	if (true == IsDown(VK_DOWN))
//	{
//		State.ChangeState("Duck_Left");
//		return;
//	}
//
//	ResultMovementUpdate(_DeltaTime);
//}
//
//void APlayer::IdleRight(float _DeltaTime)
//{
//	if (true == IsPress(VK_LEFT))
//	{
//		State.ChangeState("Run_Left");
//		return;
//	}
//
//	if (true == IsPress(VK_RIGHT))
//	{
//		State.ChangeState("Run_Right");
//		return;
//	}
//
//	if (true == IsDown('Z'))
//	{
//		State.ChangeState("Jump_Right");
//		return;
//	}
//
//	if (true == IsDown(VK_DOWN))
//	{
//		State.ChangeState("Duck_Right");
//		return;
//	}
//
//	ResultMovementUpdate(_DeltaTime);
//}

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

	ResultMovementUpdate(_DeltaTime);
}

//void APlayer::RunLeft(float _DeltaTime)
//{
//	if (true == IsUp(VK_LEFT))
//	{
//		State.ChangeState("Idle_Left");
//		return;
//	}
//
//	if (true == IsDown('Z'))
//	{
//		State.ChangeState("Jump_Left");
//		return;
//	}
//
//	if (true == IsDown(VK_DOWN))
//	{
//		State.ChangeState("Duck_Left");
//		return;
//	}
//
//	
//	SetSpeedVec(float4::Left * GetRunSpeed());
//	ResultMovementUpdate(_DeltaTime);
//}
//
//void APlayer::RunRight(float _DeltaTime)
//{
//	if (true == IsUp(VK_RIGHT))
//	{
//		State.ChangeState("Idle_Right");
//		return;
//	}
//
//	if (true == IsDown('Z'))
//	{
//		State.ChangeState("Jump_Right");
//		return;
//	}
//
//	if (true == IsDown(VK_DOWN))
//	{
//		State.ChangeState("Duck_Right");
//		return;
//	}
//
//	SetSpeedVec(float4::Right * GetRunSpeed());
//	ResultMovementUpdate(_DeltaTime);
//}

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

	if (false == DirCheck())
	{
		AnimationDirSet(Renderer, Dir);
	}

	SetSpeedVec(MoveDir(Dir) * GetRunSpeed());
	ResultMovementUpdate(_DeltaTime);
}

//void APlayer::JumpLeft(float _DeltaTime)
//{
//	float4 Pos = GetActorLocation();
//	Pos.Y = -Pos.Y;
//
//	if (true == BottomCheck(Pos, Color8Bit::Black))
//	{
//
//		if (true == IsPress(VK_DOWN))
//		{
//			State.ChangeState("Duck_Left");
//			return;
//		}
//
//		State.ChangeState("Idle_Left");
//		return;
//	}
//
//	if (true == GetAvailableParry() && true == IsDown('Z'))
//	{
//		State.ChangeState("Parry");
//		return;
//	}
//	else if(true == IsPress('Z') && 0.2f >= GetPressTime('Z'))
//	{
//		SetAvailableAddJumpVec(true);
//	}
//	else
//	{
//		SetAvailableAddJumpVec(false);
//	}
//
//	if (true == IsPress(VK_LEFT))
//	{
//		SetSpeedVec(float4::Left * GetRunSpeed());
//		Renderer->SetDir(EEngineDir::Left);
//	}
//	if (true == IsPress(VK_RIGHT))
//	{
//		SetSpeedVec(float4::Right * GetRunSpeed());
//		Renderer->SetDir(EEngineDir::Right);
//	}
//
//	if (true == IsFree(VK_LEFT) && true == IsFree(VK_RIGHT))
//	{
//		SetSpeedVec(float4::Zero);
//	}
//
//
//	ResultMovementUpdate(_DeltaTime);
//}
//
//void APlayer::JumpRight(float _DeltaTime)
//{
//	float4 Pos = GetActorLocation();
//	Pos.Y = -Pos.Y;
//
//	if (true == BottomCheck(Pos, Color8Bit::Black))
//	{
//		if (true == IsPress(VK_DOWN))
//		{
//			State.ChangeState("Duck_Right");
//			return;
//		}
//
//		State.ChangeState("Idle_Right");
//		return;
//	}
//	
//	if (true == GetAvailableParry() && true == IsDown('Z'))
//	{
//		State.ChangeState("Parry");
//		return;
//	}
//	else if(true == IsPress('Z') && 0.2f >= GetPressTime('Z'))
//	{
//		SetAvailableAddJumpVec(true);
//	}
//	else
//	{
//		SetAvailableAddJumpVec(false);
//	}
//
//	if (true == IsPress(VK_LEFT))
//	{
//		SetSpeedVec(float4::Left * GetRunSpeed());
//		Renderer->SetDir(EEngineDir::Left);
//	}
//	if (true == IsPress(VK_RIGHT))
//	{
//		SetSpeedVec(float4::Right * GetRunSpeed());
//		Renderer->SetDir(EEngineDir::Right);
//	}
//
//	if (true == IsFree(VK_LEFT) && true == IsFree(VK_RIGHT))
//	{
//		SetSpeedVec(float4::Zero);
//	}
//
//	ResultMovementUpdate(_DeltaTime);
//}

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

//void APlayer::DuckIdleLeft(float _DeltaTime)
//{
//	if (true == IsUp(VK_DOWN))
//	{
//		State.ChangeState("Idle_Left");
//		return;
//	}
//
//	if (true == IsDown(VK_RIGHT))
//	{
//		State.ChangeState("DuckIdle_Right");
//		return;
//	}
//
//	if (true == IsDown('Z'))
//	{
//		State.ChangeState("Jump_Left");
//		return;
//	}
//
//	ResultMovementUpdate(_DeltaTime);
//}
//
//void APlayer::DuckIdleRight(float _DeltaTime)
//{
//	if (true == IsUp(VK_DOWN))
//	{
//		State.ChangeState("Idle_Right");
//		return;
//	}
//
//	if (true == IsDown(VK_LEFT))
//	{
//		State.ChangeState("DuckIdle_Left");
//		return;
//	}
//
//	if (true == IsDown('Z'))
//	{
//		State.ChangeState("Jump_Right");
//		return;
//	}
//
//	ResultMovementUpdate(_DeltaTime);
//}
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

	ResultMovementUpdate(_DeltaTime);
}


//void APlayer::DuckLeft(float _DeltaTime)
//{
//	if (true == IsUp(VK_DOWN))
//	{
//		State.ChangeState("Idle_Left");
//		return;
//	}
//
//	if (true == IsDown(VK_RIGHT))
//	{
//		State.ChangeState("DuckIdle_Right");
//		return;
//	}
//
//	if (true == IsDown('Z'))
//	{
//		State.ChangeState("Jump_Left");
//		return;
//	}
//
//	ResultMovementUpdate(_DeltaTime);
//}
//
//void APlayer::DuckRight(float _DeltaTime)
//{
//	if (true == IsUp(VK_DOWN))
//	{
//		State.ChangeState("Idle_Right");
//		return;
//	}
//
//	if (true == IsDown(VK_LEFT))
//	{
//		State.ChangeState("DuckIdle_Left");
//		return;
//	}
//
//	if (true == IsDown('Z'))
//	{
//		State.ChangeState("Jump_Right");
//		return;
//	}
//
//	ResultMovementUpdate(_DeltaTime);
//}
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