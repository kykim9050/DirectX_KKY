#include "PreCompile.h"
#include <EngineCore/DefaultSceneComponent.h>

#include "Shark.h"

AShark::AShark()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("BulletRoot");
	SetRoot(Root);

	RendererInit();
	ColliderInit();
}

AShark::~AShark()
{
}

void AShark::BeginPlay()
{
	Super::BeginPlay();

	AnimationInit();
	StateInit();

	{
		SharkRenderer->ChangeAnimation(PirateBossAniName::Shark_Appear);
	}
}

void AShark::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	//State.Update(_DeltaTime);
}

void AShark::RendererInit()
{
	SharkRenderer = CreateDefaultSubObject<USpriteRenderer>("SharkRenderer");
	SharkRenderer->SetupAttachment(Root);
	SharkRenderer->SetAutoSize(1.0f, true);
	SharkRenderer->SetOrder(ERenderingOrder::SubMonster1);

	EffectRenderer = CreateDefaultSubObject<USpriteRenderer>("EffectRenderer");
	EffectRenderer->SetupAttachment(Root);
}

void AShark::AnimationInit()
{
	CreateAnimation();
	SetAnimationCallback();
}

void AShark::CreateAnimation()
{
	// Shark
	SharkRenderer->CreateAnimation(PirateBossAniName::Shark_Before_Appear, "Shark_Fin.png", 0.0416f);
	SharkRenderer->CreateAnimation(PirateBossAniName::Shark_Appear, "Shark_Appear.png", 0.0416f);

}

void AShark::SetAnimationCallback()
{

}

void AShark::ColliderInit()
{

}

void AShark::StateInit()
{

}
