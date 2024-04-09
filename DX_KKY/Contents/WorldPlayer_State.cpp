#include "PreCompile.h"
#include <EngineCore/SpriteRenderer.h>

#include "WorldPlayer.h"

void AWorldPlayer::StateInit()
{
	{
		State.CreateState("UpIdle");
		State.CreateState("RightUpIdle");
		State.CreateState("RightIdle");
		State.CreateState("RightDownIdle");
		State.CreateState("DownIdle");
		State.CreateState("LeftDownIdle");
		State.CreateState("LeftIdle");
		State.CreateState("LeftUpIdle");

		State.SetUpdateFunction("UpIdle", std::bind(&AWorldPlayer::UpIdle, this, std::placeholders::_1));
		State.SetUpdateFunction("RightUpIdle", std::bind(&AWorldPlayer::RightUpIdle, this, std::placeholders::_1));
		State.SetUpdateFunction("RightIdle", std::bind(&AWorldPlayer::RightIdle, this, std::placeholders::_1));
		State.SetUpdateFunction("RightDownIdle", std::bind(&AWorldPlayer::RightDownIdle, this, std::placeholders::_1));
		State.SetUpdateFunction("DownIdle", std::bind(&AWorldPlayer::DownIdle, this, std::placeholders::_1));
		State.SetUpdateFunction("LeftDownIdle", std::bind(&AWorldPlayer::LeftDownIdle, this, std::placeholders::_1));
		State.SetUpdateFunction("LeftIdle", std::bind(&AWorldPlayer::LeftIdle, this, std::placeholders::_1));
		State.SetUpdateFunction("LeftUpIdle", std::bind(&AWorldPlayer::LeftUpIdle, this, std::placeholders::_1));


		State.SetStartFunction("UpIdle", [=]
			{
				Renderer->ChangeAnimation("WPlayer_UpIdle");
			}
		);

		State.SetStartFunction("RightUpIdle", [=]
			{
				Renderer->ChangeAnimation("WPlayer_DiagonalUpIdle");
				Renderer->SetDir(EEngineDir::Right);
			}
		);

		State.SetStartFunction("RightIdle", [=]
			{
				Renderer->ChangeAnimation("WPlayer_StraightIdle");
				Renderer->SetDir(EEngineDir::Right);
			}
		);

		State.SetStartFunction("RightDownIdle", [=]
			{
				Renderer->ChangeAnimation("WPlayer_DiagonalDownIdle");
				Renderer->SetDir(EEngineDir::Right);
			}
		);
		
		State.SetStartFunction("DownIdle", [=]
			{
				Renderer->ChangeAnimation("WPlayer_DownIdle");
			}
		);

		State.SetStartFunction("LeftDownIdle", [=]
			{
				Renderer->ChangeAnimation("WPlayer_DiagonalDownIdle");
				Renderer->SetDir(EEngineDir::Left);
			}
		);

		State.SetStartFunction("LeftIdle", [=]
			{
				Renderer->ChangeAnimation("WPlayer_StraightIdle");
				Renderer->SetDir(EEngineDir::Left);
			}
		);

		State.SetStartFunction("LeftUpIdle", [=]
			{
				Renderer->ChangeAnimation("WPlayer_DiagonalUpIdle");
				Renderer->SetDir(EEngineDir::Left);
			}
		);
	}

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
	DirCheck();
}

void AWorldPlayer::RightUpIdle(float _DeltaTime)
{
	DirCheck();
}

void AWorldPlayer::RightIdle(float _DeltaTime)
{
	DirCheck();
}

void AWorldPlayer::RightDownIdle(float _DeltaTime)
{
	DirCheck();
}

void AWorldPlayer::DownIdle(float _DeltaTime)
{
	DirCheck();
}

void AWorldPlayer::LeftDownIdle(float _DeltaTime)
{
	DirCheck();
}

void AWorldPlayer::LeftIdle(float _DeltaTime)
{
	DirCheck();
}

void AWorldPlayer::LeftUpIdle(float _DeltaTime)
{
	DirCheck();
}


//void AWorldPlayer::KeyCheck(float _DeltaTime)
//{
//	if(true == IsPress(VK_DOWN))
//	{
//		AddActorLocation(FVector::Down * _DeltaTime * GetSpeed());
//		//State.ChangeState("DownIdle");
//
//	}
//
//	if (true == IsPress(VK_UP))
//	{
//		AddActorLocation(FVector::Up * _DeltaTime * GetSpeed());
//		//State.ChangeState("UpIdle");
//	}
//
//	if (true == IsPress(VK_RIGHT))
//	{
//		AddActorLocation(FVector::Right * _DeltaTime * GetSpeed());
//		//State.ChangeState("RightIdle");
//	}
//
//	if (true == IsPress(VK_LEFT))
//	{
//		AddActorLocation(FVector::Left * _DeltaTime * GetSpeed());
//		//State.ChangeState("LeftIdle");
//	}
//}

void AWorldPlayer::DirCheck()
{
	if (true == IsAnykeyFree())
	{
		switch (Dir)
		{
		case EWorldPlayerDir::Up:
		{
			State.ChangeState("UpIdle");
			break;
		}
		case EWorldPlayerDir::RightUp:
		{
			State.ChangeState("RightUpIdle");
			break;
		}
		case EWorldPlayerDir::Right:
		{
			State.ChangeState("RightIdle");
			break;
		}
		case EWorldPlayerDir::RightDown:
		{
			State.ChangeState("RightDownIdle");
			break;
		}
		case EWorldPlayerDir::Down:
		{
			State.ChangeState("DownIdle");
			break;
		}
		case EWorldPlayerDir::LeftDown:
		{
			State.ChangeState("LeftDownIdle");
			break;
		}
		case EWorldPlayerDir::Left:
		{
			State.ChangeState("LeftIdle");
			break;
		}
		case EWorldPlayerDir::LeftUp:
		{
			State.ChangeState("LeftUpIdle");
			break;
		}
		default:
			break;
		}

		return;
	}

	if (IsPress(VK_UP) && IsFree(VK_RIGHT))
	{
		Dir = EWorldPlayerDir::Up;
	}

	if (IsPress(VK_UP) && IsPress(VK_RIGHT))
	{
		Dir = EWorldPlayerDir::RightUp;
	}

	if (IsPress(VK_RIGHT) && IsFree(VK_DOWN))
	{
		Dir = EWorldPlayerDir::Right;
	}

	if (IsPress(VK_RIGHT) && IsPress(VK_DOWN))
	{
		Dir = EWorldPlayerDir::RightDown;
	}

	if (IsPress(VK_DOWN) && IsFree(VK_LEFT))
	{
		Dir = EWorldPlayerDir::Down;
	}

	if (IsPress(VK_DOWN) && IsPress(VK_LEFT))
	{
		Dir = EWorldPlayerDir::LeftDown;
	}

	if (IsPress(VK_LEFT) && IsFree(VK_UP))
	{
		Dir = EWorldPlayerDir::Left;
	}

	if (IsPress(VK_LEFT) && IsPress(VK_UP))
	{
		Dir = EWorldPlayerDir::LeftUp;
	}

}