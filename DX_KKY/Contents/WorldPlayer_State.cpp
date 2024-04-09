#include "PreCompile.h"
#include <EngineCore/SpriteRenderer.h>

#include "WorldPlayer.h"

void AWorldPlayer::StateInit()
{
	State.CreateState("RightDownIdle");

	State.SetUpdateFunction("RightDownIdle", std::bind(&AWorldPlayer::RightDownIdle, this, std::placeholders::_1));

	State.SetStartFunction("RightDownIdle", [=]
		{
			Renderer->ChangeAnimation("WPlayer_DiagonalDownIdle");
		}
	);

	State.ChangeState("RightDownIdle");
}


void AWorldPlayer::RightDownIdle(float _DeltaTime)
{
	KeyCheck(_DeltaTime);

	Renderer->SetAutoSize(1.0f, true);
}

void AWorldPlayer::KeyCheck(float _DeltaTime)
{
	if(true == IsPress(VK_DOWN))
	{
		AddActorLocation(FVector::Down * _DeltaTime * GetSpeed());
	}

	if (true == IsPress(VK_UP))
	{
		AddActorLocation(FVector::Up * _DeltaTime * GetSpeed());
	}

	if (true == IsPress(VK_RIGHT))
	{
		AddActorLocation(FVector::Right * _DeltaTime * GetSpeed());
	}

	if (true == IsPress(VK_LEFT))
	{
		AddActorLocation(FVector::Left * _DeltaTime * GetSpeed());
	}
}
