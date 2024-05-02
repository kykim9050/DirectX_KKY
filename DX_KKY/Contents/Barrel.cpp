#include "PreCompile.h"
#include <EngineCore/DefaultSceneComponent.h>

#include "Barrel.h"

ABarrel::ABarrel()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("BulletRoot");
	SetRoot(Root);

	RendererInit();
	ColliderInit();
}

ABarrel::~ABarrel()
{
}

void ABarrel::BeginPlay()
{
	Super::BeginPlay();

	AnimationInit();
	StateInit();

	{
		Renderer->ChangeAnimation(PirateBossAniName::Barrel_Smash_Begin);
	}
}

void ABarrel::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	//State.Update(_DeltaTime);
}

void ABarrel::RendererInit()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("BarrelRenderer");
	Renderer->SetupAttachment(Root);
}

void ABarrel::AnimationInit()
{
	CreateAnimation();
	SetAnimationCallback();
}

void ABarrel::CreateAnimation()
{
	Renderer->CreateAnimation(PirateBossAniName::Barrel_Normal_Idle, "Barrel_Normal_Idle.png", 0.047f, false, 0, 10);
	Renderer->CreateAnimation(PirateBossAniName::Barrel_Normal_IdleRev, "Barrel_Normal_Idle.png", 0.047f, false, 9, 1);
	Renderer->CreateAnimation(PirateBossAniName::Barrel_AttWait_Idle, "Pirate_Barrel_AttWait_Idle.png", 0.047f, false, 0, 10);
	Renderer->CreateAnimation(PirateBossAniName::Barrel_AttWait_IdleRev, "Pirate_Barrel_AttWait_Idle.png", 0.047f, false, 9, 1);
	Renderer->CreateAnimation(PirateBossAniName::Barrel_Drop_Begin, "Pirate_Barrel_Drop.png", 0.067f, false);
	Renderer->CreateAnimation(PirateBossAniName::Barrel_Dropping, "Pirate_Barrel_Drop.png", 0.067f, true, 1, 3);
	Renderer->CreateAnimation(PirateBossAniName::Barrel_Smash_Begin, "Pirate_Barrel_Smash.png", 0.067f, false);
	Renderer->CreateAnimation(PirateBossAniName::Barrel_Smashing, "Pirate_Barrel_Smash.png", 0.067f, true, 3, 4);

}


void ABarrel::ColliderInit()
{
	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetOrder(ERenderingOrder::Monster2);
}

void ABarrel::SetAnimationCallback()
{
	Renderer->SetFrameCallback(PirateBossAniName::Barrel_Normal_Idle, 11, [this]()
		{
			Renderer->ChangeAnimation(PirateBossAniName::Barrel_Normal_IdleRev);
		});
	Renderer->SetFrameCallback(PirateBossAniName::Barrel_Normal_IdleRev, 9, [this]()
		{
			Renderer->ChangeAnimation(PirateBossAniName::Barrel_Normal_Idle);
		});
	Renderer->SetFrameCallback(PirateBossAniName::Barrel_AttWait_Idle, 11, [this]()
		{
			Renderer->ChangeAnimation(PirateBossAniName::Barrel_AttWait_IdleRev);
		});
	Renderer->SetFrameCallback(PirateBossAniName::Barrel_AttWait_IdleRev, 9, [this]()
		{
			Renderer->ChangeAnimation(PirateBossAniName::Barrel_AttWait_Idle);
		});
	Renderer->SetFrameCallback(PirateBossAniName::Barrel_Drop_Begin, 4, [this]()
		{
			Renderer->ChangeAnimation(PirateBossAniName::Barrel_Dropping);
		});
	Renderer->SetFrameCallback(PirateBossAniName::Barrel_Smash_Begin, 5, [this]()
		{
			Renderer->ChangeAnimation(PirateBossAniName::Barrel_Smashing);
		});
}

void ABarrel::StateInit()
{

}
