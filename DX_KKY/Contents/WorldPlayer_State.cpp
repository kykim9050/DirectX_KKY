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
	if(true == IsPress(VK_UP))
	{
		State.ChangeState("UpWalk");
		return;
	}

	if (true == IsPress(VK_DOWN))
	{
		State.ChangeState("DownWalk");
		return;
	}

	if (true == IsPress(VK_LEFT))
	{
		State.ChangeState("LeftWalk");
		return;
	}

	if (true == IsPress(VK_RIGHT))
	{
		State.ChangeState("RightWalk");
		return;
	}

}

void AWorldPlayer::RightUpIdle(float _DeltaTime)
{
	if (true == IsPress(VK_UP))
	{
		State.ChangeState("UpWalk");
		return;
	}

	if (true == IsPress(VK_DOWN))
	{
		State.ChangeState("DownWalk");
		return;
	}

	if (true == IsPress(VK_LEFT))
	{
		State.ChangeState("LeftWalk");
		return;
	}

	if (true == IsPress(VK_RIGHT))
	{
		State.ChangeState("RightWalk");
		return;
	}
}

void AWorldPlayer::RightIdle(float _DeltaTime)
{
	if (true == IsPress(VK_UP))
	{
		State.ChangeState("UpWalk");
		return;
	}

	if (true == IsPress(VK_DOWN))
	{
		State.ChangeState("DownWalk");
		return;
	}

	if (true == IsPress(VK_LEFT))
	{
		State.ChangeState("LeftWalk");
		return;
	}

	if (true == IsPress(VK_RIGHT))
	{
		State.ChangeState("RightWalk");
		return;
	}
}

void AWorldPlayer::RightDownIdle(float _DeltaTime)
{
	if (true == IsPress(VK_UP))
	{
		State.ChangeState("UpWalk");
		return;
	}

	if (true == IsPress(VK_DOWN))
	{
		State.ChangeState("DownWalk");
		return;
	}

	if (true == IsPress(VK_LEFT))
	{
		State.ChangeState("LeftWalk");
		return;
	}

	if (true == IsPress(VK_RIGHT))
	{
		State.ChangeState("RightWalk");
		return;
	}
}

void AWorldPlayer::DownIdle(float _DeltaTime)
{
	if (true == IsPress(VK_UP))
	{
		State.ChangeState("UpWalk");
		return;
	}

	if (true == IsPress(VK_DOWN))
	{
		State.ChangeState("DownWalk");
		return;
	}

	if (true == IsPress(VK_LEFT))
	{
		State.ChangeState("LeftWalk");
		return;
	}

	if (true == IsPress(VK_RIGHT))
	{
		State.ChangeState("RightWalk");
		return;
	}
}

void AWorldPlayer::LeftDownIdle(float _DeltaTime)
{
	if (true == IsPress(VK_UP))
	{
		State.ChangeState("UpWalk");
		return;
	}

	if (true == IsPress(VK_DOWN))
	{
		State.ChangeState("DownWalk");
		return;
	}

	if (true == IsPress(VK_LEFT))
	{
		State.ChangeState("LeftWalk");
		return;
	}

	if (true == IsPress(VK_RIGHT))
	{
		State.ChangeState("RightWalk");
		return;
	}
}

void AWorldPlayer::LeftIdle(float _DeltaTime)
{
	if (true == IsPress(VK_UP))
	{
		State.ChangeState("UpWalk");
		return;
	}

	if (true == IsPress(VK_DOWN))
	{
		State.ChangeState("DownWalk");
		return;
	}

	if (true == IsPress(VK_LEFT))
	{
		State.ChangeState("LeftWalk");
		return;
	}

	if (true == IsPress(VK_RIGHT))
	{
		State.ChangeState("RightWalk");
		return;
	}
}

void AWorldPlayer::LeftUpIdle(float _DeltaTime)
{
	if (true == IsPress(VK_UP))
	{
		State.ChangeState("UpWalk");
		return;
	}

	if (true == IsPress(VK_DOWN))
	{
		State.ChangeState("DownWalk");
		return;
	}

	if (true == IsPress(VK_LEFT))
	{
		State.ChangeState("LeftWalk");
		return;
	}

	if (true == IsPress(VK_RIGHT))
	{
		State.ChangeState("RightWalk");
		return;
	}
}


void AWorldPlayer::UpWalk(float _DeltaTime)
{
	if (true == IsFree(VK_UP))
	{
		State.ChangeState("UpIdle");
		return;
	}

	if(true == IsPress(VK_UP))
	{
		if (true == IsPress(VK_LEFT))
		{
			State.ChangeState("LeftUpWalk");
			return;
		}

		if (true == IsPress(VK_RIGHT))
		{
			State.ChangeState("RightUpWalk");
			return;
		}
	}

	if (true == IsPress(VK_LEFT))
	{
		State.ChangeState("LeftWalk");
		return;
	}

	if (true == IsPress(VK_RIGHT))
	{
		State.ChangeState("RightWalk");
		return;
	}

	AddActorLocation(FVector::Up * _DeltaTime * GetSpeed());
}

void AWorldPlayer::RightUpWalk(float _DeltaTime)
{
	// Up, Right 둘다 때면 RightUpIdle
	if (true == IsFree(VK_UP) && true == IsFree(VK_RIGHT))
	{
		State.ChangeState("RightUpIdle");
		return;
	}

	// Up 누르고 Right는 안누를 때  UpWalk
	if (true == IsUp(VK_RIGHT))
	{
		State.ChangeState("UpWalk");
		return;
	}

	// Right 누르고 Up은 안누를 때 RightWalk
	if (true == IsUp(VK_UP))
	{
		State.ChangeState("RightWalk");
		return;
	}

	// 누르고 있을때는 AddActorLocation
	AddActorLocation(FVector::Up * _DeltaTime * GetDiagonalSpeed());
	AddActorLocation(FVector::Right * _DeltaTime * GetDiagonalSpeed());
}

void AWorldPlayer::RightWalk(float _DeltaTime)
{
	if (true == IsFree(VK_RIGHT))
	{
		State.ChangeState("RightIdle");
		return;
	}

	if (true == IsPress(VK_RIGHT))
	{
		if (true == IsPress(VK_UP))
		{
			State.ChangeState("RightUpWalk");
			return;
		}

		if (true == IsPress(VK_DOWN))
		{
			State.ChangeState("RightDownWalk");
			return;
		}
	}

	if (true == IsPress(VK_UP))
	{
		State.ChangeState("UpWalk");
		return;
	}

	if (true == IsPress(VK_DOWN))
	{
		State.ChangeState("DownWalk");
		return;
	}

	AddActorLocation(FVector::Right * _DeltaTime * GetSpeed());
}

void AWorldPlayer::RightDownWalk(float _DeltaTime)
{
	if (true == IsFree(VK_DOWN) && true == IsFree(VK_RIGHT))
	{
		State.ChangeState("RightDownIdle");
		return;
	}

	if (true == IsUp(VK_RIGHT))
	{
		State.ChangeState("DownWalk");
		return;
	}

	if (true == IsUp(VK_DOWN))
	{
		State.ChangeState("RightWalk");
		return;
	}

	AddActorLocation(FVector::Down * _DeltaTime * GetDiagonalSpeed());
	AddActorLocation(FVector::Right * _DeltaTime * GetDiagonalSpeed());
}

void AWorldPlayer::DownWalk(float _DeltaTime)
{
	if (true == IsFree(VK_DOWN))
	{
		State.ChangeState("DownIdle");
		return;
	}

	if (true == IsPress(VK_DOWN))
	{
		if (true == IsPress(VK_LEFT))
		{
			State.ChangeState("LeftDownWalk");
			return;
		}

		if (true == IsPress(VK_RIGHT))
		{
			State.ChangeState("RightDownWalk");
			return;
		}
	}

	if (true == IsPress(VK_LEFT))
	{
		State.ChangeState("LeftWalk");
		return;
	}

	if (true == IsPress(VK_RIGHT))
	{
		State.ChangeState("RightWalk");
		return;
	}

	AddActorLocation(FVector::Down * _DeltaTime * GetSpeed());
}

void AWorldPlayer::LeftDownWalk(float _DeltaTime)
{
	if (true == IsFree(VK_DOWN) && true == IsFree(VK_LEFT))
	{
		State.ChangeState("LeftDownIdle");
		return;
	}

	if (true == IsUp(VK_LEFT))
	{
		State.ChangeState("DownWalk");
		return;
	}

	if (true == IsUp(VK_DOWN))
	{
		State.ChangeState("LeftWalk");
		return;
	}

	AddActorLocation(FVector::Down * _DeltaTime * GetDiagonalSpeed());
	AddActorLocation(FVector::Left * _DeltaTime * GetDiagonalSpeed());
}

void AWorldPlayer::LeftWalk(float _DeltaTime)
{
	if (true == IsFree(VK_LEFT))
	{
		State.ChangeState("LeftIdle");
		return;
	}

	if (true == IsPress(VK_LEFT))
	{
		if (true == IsPress(VK_UP))
		{
			State.ChangeState("LeftUpWalk");
			return;
		}

		if (true == IsPress(VK_DOWN))
		{
			State.ChangeState("LeftDownWalk");
			return;
		}
	}

	if (true == IsPress(VK_UP))
	{
		State.ChangeState("UpWalk");
		return;
	}

	if (true == IsPress(VK_DOWN))
	{
		State.ChangeState("DownWalk");
		return;
	}

	AddActorLocation(FVector::Left * _DeltaTime * GetSpeed());
}

void AWorldPlayer::LeftUpWalk(float _DeltaTime)
{
	if (true == IsFree(VK_UP) && true == IsFree(VK_LEFT))
	{
		State.ChangeState("LeftUpIdle");
		return;
	}

	if (true == IsUp(VK_LEFT))
	{
		State.ChangeState("UpWalk");
		return;
	}

	if (true == IsUp(VK_UP))
	{
		State.ChangeState("LeftWalk");
		return;
	}

	AddActorLocation(FVector::Up * _DeltaTime * GetDiagonalSpeed());
	AddActorLocation(FVector::Left * _DeltaTime * GetDiagonalSpeed());
}