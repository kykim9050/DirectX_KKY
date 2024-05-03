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
}

void AShark::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
	DebugUpdate();
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
	FinRenderer->SetActive(false);

	EffectRenderer = CreateDefaultSubObject<USpriteRenderer>("EffectRenderer");
	EffectRenderer->SetupAttachment(Root);
	EffectRenderer->SetAutoSize(1.0f, true);
	EffectRenderer->SetOrder(ERenderingOrder::FrontFX);
	EffectRenderer->SetPivot(EPivot::LEFTBOTTOM);
	EffectRenderer->SetActive(false);
}

void AShark::AnimationInit()
{
	CreateAnimation();
	SetAnimationCallback();
}

void AShark::CreateAnimation()
{
	// Shark
	SharkRenderer->CreateAnimation(PirateBossAniName::Shark_Appear, "Shark_Appear.png", 0.067f);
	SharkRenderer->CreateAnimation(PirateBossAniName::Shark_Chomp1, "Shark_Chomp1.png", 0.0416f, false);
	SharkRenderer->CreateAnimation(PirateBossAniName::Shark_Chomp2, "Shark_Chomp2.png", 0.0416f, false);
	SharkRenderer->CreateAnimation(PirateBossAniName::Shark_Leave, "Shark_Leave.png", 0.067f, true);

	// ShartFin
	FinRenderer->CreateAnimation(PirateBossAniName::Shark_Before_Appear, "Shark_Fin.png", 0.0416f);

	// Effect
	EffectRenderer->CreateAnimation(PirateBossAniName::Shark_Appear_Effect, "Shark_Appear_Effect.png", 0.0416f, false);
}

void AShark::SetAnimationCallback()
{
	SharkRenderer->SetFrameCallback(PirateBossAniName::Shark_Chomp1, 10, [this]()
		{
			SharkRenderer->ChangeAnimation(PirateBossAniName::Shark_Chomp2);
		});

	EffectRenderer->SetFrameCallback(PirateBossAniName::Shark_Appear_Effect, 22, [this]()
		{
			EffectRenderer->SetActive(false);
		});

}

void AShark::ColliderInit()
{

}

void AShark::StateInit()
{
	{
		State.CreateState(PirateBossState::Shark_Appear_Intro);
	}

	{
		State.SetStartFunction(PirateBossState::Shark_Appear_Intro, [this]()
			{
				SetSpeedVec(float4::Left * AppearIntroSpeed);
				FinRenderer->SetActive(true);
				FinRenderer->ChangeAnimation(PirateBossAniName::Shark_Before_Appear);
			});
	}

	{
		State.SetUpdateFunction(PirateBossState::Shark_Appear_Intro, std::bind(&AShark::Appear_Intro, this, std::placeholders::_1));
	}

	{
		State.SetEndFunction(PirateBossState::Shark_Appear_Intro, [this]()
			{
				SetSpeedVec(float4::Zero);
				FinRenderer->SetActive(false);
			});
	}

	State.ChangeState(PirateBossState::Shark_Appear_Intro);
}

void AShark::Appear_Intro(float _DeltaTime)
{

	ResultMovementUpdate(_DeltaTime);
}

void AShark::DebugUpdate()
{
	{
		std::string Msg = std::format("Shark Pos : {}\n", GetActorLocation().ToString());
		UEngineDebugMsgWindow::PushMsg(Msg);
	}
}