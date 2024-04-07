#include "PreCompile.h"
#include "Player.h"
#include <EngineCore/Renderer.h>
#include <EngineCore/SpriteRenderer.h>

APlayer::APlayer() 
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("PlayerRenderer");
}

APlayer::~APlayer() 
{
}

void APlayer::BeginPlay()
{
	Super::BeginPlay();

	//Renderer->SetSprite("");


}

void APlayer::Tick(float _DeltaTime)
{
	// 위에 뭔가를 쳐야할때도 있다.
	Super::Tick(_DeltaTime);

	//float Speed = 100.0f;

	//if (true == UEngineInput::IsPress('A'))
	//{
	//	AddActorLocation(FVector::Left * _DeltaTime * Speed);
	//}

	//if (true == UEngineInput::IsPress('D'))
	//{
	//	AddActorLocation(FVector::Right * _DeltaTime * Speed);
	//}

	//if (true == UEngineInput::IsPress('W'))
	//{
	//	AddActorLocation(FVector::Up * _DeltaTime * Speed);
	//}

	//if (true == UEngineInput::IsPress('S'))
	//{
	//	AddActorLocation(FVector::Down * _DeltaTime * Speed);
	//}

	//if (true == UEngineInput::IsPress(VK_NUMPAD1))
	//{
	//	Color.X += _DeltaTime;
	//}

	//if (true == UEngineInput::IsPress(VK_NUMPAD2))
	//{
	//	Color.X -= _DeltaTime;
	//}

	//if (true == UEngineInput::IsPress(VK_NUMPAD4))
	//{
	//	Color.Y += _DeltaTime;
	//}

	//if (true == UEngineInput::IsPress(VK_NUMPAD5))
	//{
	//	Color.Y -= _DeltaTime;
	//}

	//if (true == UEngineInput::IsPress(VK_NUMPAD7))
	//{
	//	Color.Z += _DeltaTime;
	//}

	//if (true == UEngineInput::IsPress(VK_NUMPAD8))
	//{
	//	Color.Z -= _DeltaTime;
	//}



	//// Renderer->SetConstanctBuffer("Ftransform", GetTransform());


}