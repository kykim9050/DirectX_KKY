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
		Renderer->ChangeAnimation(PirateBossAniName::Barrel_Normal_Idle);
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
	Renderer->CreateAnimation(PirateBossAniName::Barrel_Normal_Idle, "Barrel_Normal_Idle.png", 0.047f, true, 0, 10);
	Renderer->CreateAnimation(PirateBossAniName::Barrel_Normal_IdleRev, "Barrel_Normal_Idle.png", 0.047f, true, 9, 1);

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
}

void ABarrel::StateInit()
{

}
