#include "PreCompile.h"
#include <EngineCore/SpriteRenderer.h>

#include "WorldPlayer.h"

void AWorldPlayer::StateInit()
{
	State.CreateState("RightDownIdle");
	State.CreateState("RightIdle");
	State.CreateState("UpIdle");
	State.CreateState("DownIdle");
	State.CreateState("LeftIdle");

	State.SetUpdateFunction("RightDownIdle", std::bind(&AWorldPlayer::RightDownIdle, this, std::placeholders::_1));
	State.SetUpdateFunction("RightIdle", std::bind(&AWorldPlayer::RightIdle, this, std::placeholders::_1));
	State.SetUpdateFunction("UpIdle", std::bind(&AWorldPlayer::UpIdle, this, std::placeholders::_1));
	State.SetUpdateFunction("DownIdle", std::bind(&AWorldPlayer::DownIdle, this, std::placeholders::_1));
	State.SetUpdateFunction("LeftIdle", std::bind(&AWorldPlayer::LeftIdle, this, std::placeholders::_1));

	State.SetStartFunction("RightDownIdle", [=]
		{
			Renderer->ChangeAnimation("WPlayer_DiagonalDownIdle");
		}
	);
	State.SetStartFunction("RightIdle", [=]
		{
			Renderer->ChangeAnimation("WPlayer_StraightIdle");
			Renderer->SetDir(EEngineDir::Right);
		}
	);
	State.SetStartFunction("UpIdle", [=]
		{
			Renderer->ChangeAnimation("WPlayer_UpIdle");
		}
	);
	State.SetStartFunction("DownIdle", [=]
		{
			Renderer->ChangeAnimation("WPlayer_DownIdle");
		}
	);
	State.SetStartFunction("LeftIdle", [=]
		{
			Renderer->ChangeAnimation("WPlayer_StraightIdle");
			Renderer->SetDir(EEngineDir::Left);
		}
	);


	Renderer->SetAutoSize(1.0f, true);
	State.ChangeState("RightDownIdle");



	//Renderer->CreateAnimation("WPlayer_DiagonalUpIdle", "DiagonalUpIdle", 0.067f);
	//Renderer->CreateAnimation("WPlayer_UpWalk", "UpWalk", 0.067f);
	//Renderer->CreateAnimation("WPlayer_DownWalk", "DownWalk", 0.067f);
	//Renderer->CreateAnimation("WPlayer_DiagonalUpWalk", "DiagonalUpWalk", 0.067f);
	//Renderer->CreateAnimation("WPlayer_DiagonalDownWalk", "DiagonalDownWalk", 0.067f);
	//Renderer->CreateAnimation("WPlayer_StraightWalk", "StraightWalk", 0.067f);
}


void AWorldPlayer::UpIdle(float _DeltaTime)
{
	KeyCheck(_DeltaTime);
}

void AWorldPlayer::RightIdle(float _DeltaTime)
{
	KeyCheck(_DeltaTime);
}

void AWorldPlayer::RightDownIdle(float _DeltaTime)
{
	KeyCheck(_DeltaTime);
}

void AWorldPlayer::DownIdle(float _DeltaTime)
{
	KeyCheck(_DeltaTime);
}

void AWorldPlayer::LeftIdle(float _DeltaTime)
{
	KeyCheck(_DeltaTime);
}


void AWorldPlayer::KeyCheck(float _DeltaTime)
{
	if(true == IsPress(VK_DOWN))
	{
		AddActorLocation(FVector::Down * _DeltaTime * GetSpeed());
		State.ChangeState("DownIdle");
	}

	if (true == IsPress(VK_UP))
	{
		AddActorLocation(FVector::Up * _DeltaTime * GetSpeed());
		State.ChangeState("UpIdle");
	}

	if (true == IsPress(VK_RIGHT))
	{
		AddActorLocation(FVector::Right * _DeltaTime * GetSpeed());
		State.ChangeState("RightIdle");
	}

	if (true == IsPress(VK_LEFT))
	{
		AddActorLocation(FVector::Left * _DeltaTime * GetSpeed());
		State.ChangeState("LeftIdle");
	}
}
