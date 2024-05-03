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
		EffectRenderer->ChangeAnimation(PirateBossAniName::Shark_Appear_Effect);
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
	SharkRenderer->SetActive(false);

	FinRenderer = CreateDefaultSubObject<USpriteRenderer>("FinRenderer");
	FinRenderer->SetupAttachment(Root);
	FinRenderer->SetAutoSize(1.0f, true);
	FinRenderer->SetOrder(ERenderingOrder::SharkFin);

	EffectRenderer = CreateDefaultSubObject<USpriteRenderer>("EffectRenderer");
	EffectRenderer->SetupAttachment(Root);
	EffectRenderer->SetAutoSize(1.0f, true);
	EffectRenderer->SetOrder(ERenderingOrder::FrontFX);
	EffectRenderer->SetPivot(EPivot::LEFTBOTTOM);
	//EffectRenderer->SetActive(false);
}

void AShark::AnimationInit()
{
	CreateAnimation();
	SetAnimationCallback();
}

void AShark::CreateAnimation()
{
	// Shark
	SharkRenderer->CreateAnimation(PirateBossAniName::Shark_Appear, "Shark_Appear.png", 0.0416f);
	SharkRenderer->CreateAnimation(PirateBossAniName::Shark_Chomp1, "Shark_Chomp1.png", 0.0416f, false);
	SharkRenderer->CreateAnimation(PirateBossAniName::Shark_Chomp2, "Shark_Chomp2.png", 0.0416f, false);
	SharkRenderer->CreateAnimation(PirateBossAniName::Shark_Leave, "Shark_Leave.png", 0.067f, true);

	// ShartFin
	FinRenderer->CreateAnimation(PirateBossAniName::Shark_Before_Appear, "Shark_Fin.png", 0.0416f);

	// Effect
	EffectRenderer->CreateAnimation(PirateBossAniName::Shark_Appear_Effect, "Shark_Appear_Effect.png", 0.0416f, true);
}

void AShark::SetAnimationCallback()
{
	SharkRenderer->SetFrameCallback(PirateBossAniName::Shark_Chomp1, 10, [this]()
		{
			SharkRenderer->ChangeAnimation(PirateBossAniName::Shark_Chomp2);
		});

}

void AShark::ColliderInit()
{

}

void AShark::StateInit()
{

}
