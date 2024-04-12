#include "PreCompile.h"

#include "Player.h"
#include <EngineCore/SpriteRenderer.h>
#include "MoveUnit.h"

void APlayer::StateInit()
{
	{
		State.CreateState("Idle_Left");
		State.CreateState("Idle_Right");
		State.CreateState("Run_Left");
		State.CreateState("Run_Right");
		State.CreateState("Jump_Left");
		State.CreateState("Jump_Right");

		State.SetUpdateFunction("Idle_Left", std::bind(&APlayer::IdleLeft, this, std::placeholders::_1));
		State.SetUpdateFunction("Idle_Right", std::bind(&APlayer::IdleRight, this, std::placeholders::_1));
		State.SetUpdateFunction("Run_Left", std::bind(&APlayer::RunLeft, this, std::placeholders::_1));
		State.SetUpdateFunction("Run_Right", std::bind(&APlayer::RunRight, this, std::placeholders::_1));
		State.SetUpdateFunction("Jump_Left", std::bind(&APlayer::JumpLeft, this, std::placeholders::_1));
		State.SetUpdateFunction("Jump_Right", std::bind(&APlayer::JumpRight, this, std::placeholders::_1));


		State.SetStartFunction("Idle_Left", [this]
			{
				SetSpeedVec(float4::Zero);
				SetJumpVec(float4::Zero);
				Dir = EActorDir::Left;
				Renderer->ChangeAnimation("Player_Idle");
				Renderer->SetDir(EEngineDir::Left);
			}
		);
		State.SetStartFunction("Idle_Right", [this]
			{
				SetSpeedVec(float4::Zero);
				SetJumpVec(float4::Zero);
				Dir = EActorDir::Right;
				Renderer->ChangeAnimation("Player_Idle");
				Renderer->SetDir(EEngineDir::Right);
			}
		);
		State.SetStartFunction("Run_Left", [this]
			{
				Dir = EActorDir::Left;
				Renderer->ChangeAnimation("Player_Run");
				Renderer->SetDir(EEngineDir::Left);
			}
		);
		State.SetStartFunction("Run_Right", [this]
			{
				Dir = EActorDir::Right;
				Renderer->ChangeAnimation("Player_Run");
				Renderer->SetDir(EEngineDir::Right);
			}
		);
		State.SetStartFunction("Jump_Left", [this]
			{
				Dir = EActorDir::Left;
				AddActorLocation(float4::Up * 4);
				SetJumpVec(float4::Up * GetJumpVal());
				Renderer->ChangeAnimation("Player_Jump");
				Renderer->SetDir(EEngineDir::Left);
			}
		);
		State.SetStartFunction("Jump_Right", [this]
			{
				Dir = EActorDir::Right;
				AddActorLocation(float4::Up * 4);
				SetJumpVec(float4::Up * GetJumpVal());
				Renderer->ChangeAnimation("Player_Jump");
				Renderer->SetDir(EEngineDir::Right);
			}
		);


	}

	State.ChangeState("Idle_Right");
}

void APlayer::IdleLeft(float _DeltaTime)
{
	if (true == IsPress(VK_LEFT))
	{
		State.ChangeState("Run_Left");
		return;
	}

	if (true == IsPress(VK_RIGHT))
	{
		State.ChangeState("Run_Right");
		return;
	}

	if (true == IsPress('Z'))
	{
		State.ChangeState("Jump_Left");
		return;
	}

	ResultMovementUpdate(_DeltaTime);
}

void APlayer::IdleRight(float _DeltaTime)
{
	if (true == IsPress(VK_LEFT))
	{
		State.ChangeState("Run_Left");
		return;
	}

	if (true == IsPress(VK_RIGHT))
	{
		State.ChangeState("Run_Right");
		return;
	}

	if (true == IsPress('Z'))
	{
		State.ChangeState("Jump_Right");
		return;
	}

	ResultMovementUpdate(_DeltaTime);
}

void APlayer::RunLeft(float _DeltaTime)
{
	if (true == IsUp(VK_LEFT))
	{
		State.ChangeState("Idle_Left");
		return;
	}

	if (true == IsPress('Z'))
	{
		State.ChangeState("Jump_Left");
		return;
	}

	
	SetSpeedVec(float4::Left * GetRunSpeed());
	ResultMovementUpdate(_DeltaTime);
}

void APlayer::RunRight(float _DeltaTime)
{
	if (true == IsUp(VK_RIGHT))
	{
		State.ChangeState("Idle_Right");
		return;
	}

	if (true == IsPress('Z'))
	{
		State.ChangeState("Jump_Right");
		return;
	}

	SetSpeedVec(float4::Right * GetRunSpeed());
	ResultMovementUpdate(_DeltaTime);
}

void APlayer::JumpLeft(float _DeltaTime)
{
	float4 Pos = GetActorLocation();
	Pos.Y = -Pos.Y;

	if (true == BottomCheck(Pos, Color8Bit::Black))
	{
		State.ChangeState("Idle_Left");
		return;
	}

	if (true == IsPress(VK_LEFT))
	{
		SetSpeedVec(float4::Left * GetRunSpeed());
	}
	if (true == IsPress(VK_RIGHT))
	{
		SetSpeedVec(float4::Right * GetRunSpeed());
	}


	ResultMovementUpdate(_DeltaTime);
}

void APlayer::JumpRight(float _DeltaTime)
{
	float4 Pos = GetActorLocation();
	Pos.Y = -Pos.Y;

	if (true == BottomCheck(Pos, Color8Bit::Black))
	{
		State.ChangeState("Idle_Right");
		return;
	}

	if (true == IsPress(VK_LEFT))
	{
		SetSpeedVec(float4::Left * GetRunSpeed());
	}
	if (true == IsPress(VK_RIGHT))
	{
		SetSpeedVec(float4::Right * GetRunSpeed());
	}

	ResultMovementUpdate(_DeltaTime);
}
