#include "PreCompile.h"
#include "Player.h"
#include <EngineCore/Renderer.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>

APlayer::APlayer() 
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("PlayerRoot");
	SetRoot(Root);

	Renderer = CreateDefaultSubObject<USpriteRenderer>("PlayerRenderer");
	Renderer->SetupAttachment(Root);

	InputOn();
}

APlayer::~APlayer() 
{
}

void APlayer::BeginPlay()
{
	Super::BeginPlay();

	CreatePlayerAnimation();
	
	Renderer->ChangeAnimation("Player_Idle");
	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetOrder(ERenderingOrder::Player);

	StateInit();
}

void APlayer::Tick(float _DeltaTime)
{
	// 위에 뭔가를 쳐야할때도 있다.
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}

void APlayer::CreatePlayerAnimation()
{
	Renderer->CreateAnimation("Player_Idle", "Cuphead_Idle", 0.04f);
	Renderer->CreateAnimation("Player_Run", "CupHead_Run", 0.033f);
	Renderer->CreateAnimation("Player_Jump", "CupHead_Jump", 0.034f);
	Renderer->CreateAnimation("Player_Parry", "CupHead_Parry", 0.033f, false);

	Renderer->CreateAnimation("Player_Aim_Straight", "CupHead_Aim_Straight", 0.04f);
	Renderer->CreateAnimation("Player_Aim_Up", "CupHead_Aim_Up", 0.04f);
	Renderer->CreateAnimation("Player_Aim_Down", "CupHead_Aim_Down", 0.04f);
	Renderer->CreateAnimation("Player_Aim_DiagonalUp", "CupHead_Aim_DiagonalUp", 0.04f);
	Renderer->CreateAnimation("Player_Aim_DiagonalDown", "CupHead_Aim_DiagonalDown", 0.04f);

	Renderer->CreateAnimation("Player_Duck", "CupHead_Duck", 0.033f, false);
	Renderer->CreateAnimation("Player_DuckIdle", "CupHead_DuckIdle", 0.04f);

	Renderer->CreateAnimation("Player_Dash", "CupHead_Dash", 0.034f, false);
	Renderer->CreateAnimation("Player_Dash_Air", "CupHead_Dash_Air", 0.034f, false);

	Renderer->CreateAnimation("Player_Run_Shoot_Straight", "CupHead_Run_Shoot_Straight", 0.033f);
	Renderer->CreateAnimation("Player_Run_Shoot_DiagonalUp", "CupHead_Run_Shoot_DiagonalUp", 0.033f);

	Renderer->CreateAnimation("Player_Shoot_Straight", "CupHead_Shoot_Straight", 0.033f, false);
	Renderer->CreateAnimation("Player_Shoot_Up", "CupHead_Shoot_Up", 0.033f, false);
	Renderer->CreateAnimation("Player_Shoot_Down", "CupHead_Shoot_Down", 0.033f, false);
	Renderer->CreateAnimation("Player_Shoot_DiagonalUp", "CupHead_Shoot_DiagonalUp", 0.033f, false);
	Renderer->CreateAnimation("Player_Shoot_DiagonalDown", "CupHead_Shoot_DiagonalDown", 0.033f, false);
	Renderer->CreateAnimation("Player_Duck_Shoot", "CupHead_Duck_Shoot", 0.033f, false);

	Renderer->CreateAnimation("Player_SSAir_Straight", "CupHead_SSAir_Straight", 0.0416f, false);
	Renderer->CreateAnimation("Player_SSAir_Up", "CupHead_SSAir_Up", 0.0416f, false);
	Renderer->CreateAnimation("Player_SSAir_Down", "CupHead_SSAir_Down", 0.0416f, false);
	Renderer->CreateAnimation("Player_SSAir_DiagonalUp", "CupHead_SSAir_DiagonalUp", 0.0416f, false);
	Renderer->CreateAnimation("Player_SSAir_DiagonalDown", "CupHead_SSAir_DiagonalDown", 0.0416f, false);

	Renderer->CreateAnimation("Player_SSGround_Straight", "CupHead_SSGround_Straight", 0.0416f, false);
	Renderer->CreateAnimation("Player_SSGround_Up", "CupHead_SSGround_Up", 0.0416f, false);
	Renderer->CreateAnimation("Player_SSGround_Down", "CupHead_SSGround_Down", 0.0416f, false);
	Renderer->CreateAnimation("Player_SSGround_DiagonalUp", "CupHead_SSGround_DiagonalUp", 0.0416f, false);
	Renderer->CreateAnimation("Player_SSGround_DiagonalDown", "CupHead_SSGround_DiagonalDown", 0.0416f, false);

	Renderer->CreateAnimation("Player_Hit_Ground", "CupHead_Hit_Ground", 0.05f, false);

	Renderer->CreateAnimation("Player_Scared", "CupHead_Scared", 0.034f, false);
}