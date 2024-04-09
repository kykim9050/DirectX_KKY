#include "PreCompile.h"
#include <EngineCore/SpriteRenderer.h>

#include "WorldPlayer.h"

void AWorldPlayer::StateInit()
{
	State.CreateState("Idle");

	State.SetUpdateFunction("Idle", std::bind(&AWorldPlayer::Idle, this, std::placeholders::_1));

	State.SetStartFunction("Idle", [=]
		{
			Renderer->ChangeAnimation("WPlayer_Idle");
		}
	);

	State.ChangeState("Idle");
}


void AWorldPlayer::Idle(float _DeltaTime)
{

	if (true == IsPress(VK_LEFT))
	{
		AddActorLocation(FVector::Left * _DeltaTime * GetSpeed());
	}

	if (true == IsPress(VK_RIGHT))
	{
		AddActorLocation(FVector::Right * _DeltaTime * GetSpeed());
	}

	if (true == IsPress(VK_UP))
	{
		AddActorLocation(FVector::Up * _DeltaTime * GetSpeed());
	}

	if (true == IsPress(VK_DOWN))
	{
		AddActorLocation(FVector::Down * _DeltaTime * GetSpeed());
	}

	Renderer->SetAutoSize(1.0f, true);
}