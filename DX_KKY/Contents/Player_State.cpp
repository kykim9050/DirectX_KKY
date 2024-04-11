#include "PreCompile.h"

#include "Player.h"
#include <EngineCore/SpriteRenderer.h>


void APlayer::StateInit()
{
	{
		State.CreateState("Idle_Left");
		State.CreateState("Idle_Right");
		State.CreateState("Run_Left");
		State.CreateState("Run_Right");

		State.SetUpdateFunction("Idle_Left", std::bind(&APlayer::IdleLeft, this, std::placeholders::_1));
		State.SetUpdateFunction("Idle_Right", std::bind(&APlayer::IdleRight, this, std::placeholders::_1));
		State.SetUpdateFunction("Run_Left", std::bind(&APlayer::RunLeft, this, std::placeholders::_1));
		State.SetUpdateFunction("Run_Right", std::bind(&APlayer::RunRight, this, std::placeholders::_1));

		State.SetStartFunction("Idle_Left", [this]
			{
				Renderer->ChangeAnimation("Player_Idle");
				Renderer->SetDir(EEngineDir::Left);
			}
		);
		State.SetStartFunction("Idle_Right", [this]
			{
				Renderer->ChangeAnimation("Player_Idle");
				Renderer->SetDir(EEngineDir::Right);
			}
		);
		State.SetStartFunction("Run_Left", [this]
			{
				Renderer->ChangeAnimation("Player_Run");
				Renderer->SetDir(EEngineDir::Left);
			}
		);
		State.SetStartFunction("Run_Right", [this]
			{
				Renderer->ChangeAnimation("Player_Run");
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
}

void APlayer::RunLeft(float _DeltaTime)
{
	if (true == IsUp(VK_LEFT))
	{
		State.ChangeState("Idle_Left");
		return;
	}

	//if (true == IsPress(VK_RIGHT))
	//{
	//	State.ChangeState("Run_Right");
	//	return;
	//}

	AddActorLocation(FVector::Left * _DeltaTime * GetRunSpeed());
}

void APlayer::RunRight(float _DeltaTime)
{
	if (true == IsUp(VK_RIGHT))
	{
		State.ChangeState("Idle_Right");
		return;
	}

	//if (true == IsPress(VK_RIGHT))
	//{
	//	State.ChangeState("Run_Right");
	//	return;
	//}

	AddActorLocation(FVector::Right * _DeltaTime * GetRunSpeed());
}