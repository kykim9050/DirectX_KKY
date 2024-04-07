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
	
	SetActorScale3D(FVector(200.0f, 200.0f, 0.0f));

	Renderer->SetSprite("Cuphead_Idle");

	Renderer->CreateAnimation("Player_Idle", "Cuphead_Idle", 0.04f);
	Renderer->CreateAnimation("Player_Run", "CupHead_Run", 0.033f);
	Renderer->CreateAnimation("Player_Jump", "CupHead_Jump", 0.034f);
	Renderer->CreateAnimation("Player_Parry", "CupHead_Parry", 0.033f, false);
	Renderer->CreateAnimation("Player_Aim_Straight", "CupHead_Aim_Straight", 0.01f, false);

	Renderer->ChangeAnimation("Player_Idle");


	//renderer_->CreateAnimationFolder("Aim_Straight");
	//renderer_->CreateAnimationFolder("Aim_Up");
	//renderer_->CreateAnimationFolder("Aim_Down");
	//renderer_->CreateAnimationFolder("Aim_DiagonalUp");
	//renderer_->CreateAnimationFolder("Aim_DiagonalDown");

	//renderer_->CreateAnimationFolder("Duck", "Duck", 0.033f, false);
	//renderer_->CreateAnimationFolder("DuckIdle", "DuckIdle", 0.04f);

	//renderer_->CreateAnimationFolder("Dash", 0.034f, false);
	//renderer_->CreateAnimationFolder("Dash_Air", 0.034f, false);

	//renderer_->CreateAnimationFolder("Run_Shoot_Straight");
	//renderer_->CreateAnimationFolder("Run_Shoot_DiagonalUp");

	//renderer_->CreateAnimationFolder("Shoot_Straight");
	//renderer_->CreateAnimationFolder("Shoot_Up");
	//renderer_->CreateAnimationFolder("Shoot_Down");
	//renderer_->CreateAnimationFolder("Shoot_DiagonalUp");
	//renderer_->CreateAnimationFolder("Shoot_DiagonalDown");

	//renderer_->CreateAnimationFolder("SSAir_Straight", 0.0416f, false);
	//renderer_->CreateAnimationFolder("SSAir_Up", 0.0416f, false);
	//renderer_->CreateAnimationFolder("SSAir_Down", 0.0416f, false);
	//renderer_->CreateAnimationFolder("SSAir_DiagonalUp", 0.0416f, false);
	//renderer_->CreateAnimationFolder("SSAir_DiagonalDown", 0.0416f, false);

	//renderer_->CreateAnimationFolder("SSGround_Straight", 0.0416f, false);
	//renderer_->CreateAnimationFolder("SSGround_Up", 0.0416f, false);
	//renderer_->CreateAnimationFolder("SSGround_Down", 0.0416f, false);
	//renderer_->CreateAnimationFolder("SSGround_DiagonalUp", 0.0416f, false);
	//renderer_->CreateAnimationFolder("SSGround_DiagonalDown", 0.0416f, false);

	//renderer_->CreateAnimationFolder("Duck_Shoot");

	//renderer_->CreateAnimationFolder("Hit_Ground", 0.05f, false);

	//renderer_->CreateAnimationFolder("Scared", 0.034f, false);




}

void APlayer::Tick(float _DeltaTime)
{
	// 위에 뭔가를 쳐야할때도 있다.
	Super::Tick(_DeltaTime);

	float Speed = 100.0f;

	if (true == UEngineInput::IsDown(VK_LEFT) || true == UEngineInput::IsPress(VK_RIGHT))
	{
		Renderer->ChangeAnimation("Player_Run");
	}

	if (true == UEngineInput::IsDown('Z'))
	{
		Renderer->ChangeAnimation("Player_Jump");
	}
	
	if (true == UEngineInput::IsDown('S'))
	{
		Renderer->ChangeAnimation("Player_Idle");
	}

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