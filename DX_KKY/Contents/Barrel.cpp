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
}

void ABarrel::ColliderInit()
{
	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetOrder(ERenderingOrder::Monster2);
}

void ABarrel::SetAnimationCallback()
{

}

void ABarrel::StateInit()
{

}
