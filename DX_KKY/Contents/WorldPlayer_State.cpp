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

		State.CreateState("UpWalk");
		State.CreateState("RightUpWalk");
		State.CreateState("RightWalk");
		State.CreateState("RightDownWalk");
		State.CreateState("DownWalk");
		State.CreateState("LeftDownWalk");
		State.CreateState("LeftWalk");
		State.CreateState("LeftUpWalk");


		State.SetUpdateFunction("UpIdle", std::bind(&AWorldPlayer::UpIdle, this, std::placeholders::_1));
		State.SetUpdateFunction("RightUpIdle", std::bind(&AWorldPlayer::RightUpIdle, this, std::placeholders::_1));
		State.SetUpdateFunction("RightIdle", std::bind(&AWorldPlayer::RightIdle, this, std::placeholders::_1));
		State.SetUpdateFunction("RightDownIdle", std::bind(&AWorldPlayer::RightDownIdle, this, std::placeholders::_1));
		State.SetUpdateFunction("DownIdle", std::bind(&AWorldPlayer::DownIdle, this, std::placeholders::_1));
		State.SetUpdateFunction("LeftDownIdle", std::bind(&AWorldPlayer::LeftDownIdle, this, std::placeholders::_1));
		State.SetUpdateFunction("LeftIdle", std::bind(&AWorldPlayer::LeftIdle, this, std::placeholders::_1));
		State.SetUpdateFunction("LeftUpIdle", std::bind(&AWorldPlayer::LeftUpIdle, this, std::placeholders::_1));

		State.SetUpdateFunction("UpWalk", std::bind(&AWorldPlayer::UpWalk, this, std::placeholders::_1));
		State.SetUpdateFunction("RightUpWalk", std::bind(&AWorldPlayer::RightUpWalk, this, std::placeholders::_1));
		State.SetUpdateFunction("RightWalk", std::bind(&AWorldPlayer::RightWalk, this, std::placeholders::_1));
		State.SetUpdateFunction("RightDownWalk", std::bind(&AWorldPlayer::RightDownWalk, this, std::placeholders::_1));
		State.SetUpdateFunction("DownWalk", std::bind(&AWorldPlayer::DownWalk, this, std::placeholders::_1));
		State.SetUpdateFunction("LeftDownWalk", std::bind(&AWorldPlayer::LeftDownWalk, this, std::placeholders::_1));
		State.SetUpdateFunction("LeftWalk", std::bind(&AWorldPlayer::LeftWalk, this, std::placeholders::_1));
		State.SetUpdateFunction("LeftUpWalk", std::bind(&AWorldPlayer::LeftUpWalk, this, std::placeholders::_1));


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
	
		State.SetStartFunction("UpWalk", [=]
			{
				Renderer->ChangeAnimation("WPlayer_UpWalk");
			}
		);
		State.SetStartFunction("RightUpWalk", [=]
			{
				Renderer->ChangeAnimation("WPlayer_DiagonalUpWalk");
				Renderer->SetDir(EEngineDir::Right);
			}
		);
		State.SetStartFunction("RightWalk", [=]
			{
				Renderer->ChangeAnimation("WPlayer_StraightWalk");
				Renderer->SetDir(EEngineDir::Right);
			}
		);
		State.SetStartFunction("RightDownWalk", [=]
			{
				Renderer->ChangeAnimation("WPlayer_DiagonalDownWalk");
				Renderer->SetDir(EEngineDir::Right);
			}
		);
		State.SetStartFunction("DownWalk", [=]
			{
				Renderer->ChangeAnimation("WPlayer_DownWalk");
			}
		);
		State.SetStartFunction("LeftDownWalk", [=]
			{
				Renderer->ChangeAnimation("WPlayer_DiagonalDownWalk");
				Renderer->SetDir(EEngineDir::Left);
			}
		);
		State.SetStartFunction("LeftWalk", [=]
			{
				Renderer->ChangeAnimation("WPlayer_StraightWalk");
				Renderer->SetDir(EEngineDir::Left);
			}
		);
		State.SetStartFunction("LeftUpWalk", [=]
			{
				Renderer->ChangeAnimation("WPlayer_DiagonalUpWalk");
				Renderer->SetDir(EEngineDir::Left);
			}
		);
	}

	Renderer->SetAutoSize(1.0f, true);
	State.ChangeState("RightDownIdle");
}

void AWorldPlayer::UpIdle(float _DeltaTime)
{

}

void AWorldPlayer::RightUpIdle(float _DeltaTime)
{

}

void AWorldPlayer::RightIdle(float _DeltaTime)
{

}

void AWorldPlayer::RightDownIdle(float _DeltaTime)
{

}

void AWorldPlayer::DownIdle(float _DeltaTime)
{

}

void AWorldPlayer::LeftDownIdle(float _DeltaTime)
{
	
}

void AWorldPlayer::LeftIdle(float _DeltaTime)
{
	
}

void AWorldPlayer::LeftUpIdle(float _DeltaTime)
{
	
}


void AWorldPlayer::UpWalk(float _DeltaTime)
{

}

void AWorldPlayer::RightUpWalk(float _DeltaTime)
{

}

void AWorldPlayer::RightWalk(float _DeltaTime)
{

}

void AWorldPlayer::RightDownWalk(float _DeltaTime)
{

}

void AWorldPlayer::DownWalk(float _DeltaTime)
{

}

void AWorldPlayer::LeftDownWalk(float _DeltaTime)
{

}

void AWorldPlayer::LeftWalk(float _DeltaTime)
{

}

void AWorldPlayer::LeftUpWalk(float _DeltaTime)
{

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