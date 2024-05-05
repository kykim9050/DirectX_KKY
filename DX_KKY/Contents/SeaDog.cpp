#include "PreCompile.h"
#include <EngineCore/DefaultSceneComponent.h>

#include "SeaDog.h"

ASeaDog::ASeaDog()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("BulletRoot");
	SetRoot(Root);

	RendererInit();
	ColliderInit();
}

ASeaDog::~ASeaDog()
{
}

void ASeaDog::BeginPlay()
{
	Super::BeginPlay();

	AnimationInit();
	StateInit();
}

void ASeaDog::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}

void ASeaDog::RendererInit()
{
	SeaDogRenderer = CreateDefaultSubObject<USpriteRenderer>("SeaDogRenderer");
	SeaDogRenderer->SetupAttachment(Root);
	SeaDogRenderer->SetAutoSize(1.0f, true);
	SeaDogRenderer->SetOrder(ERenderingOrder::SubMonster1);

	//EffectRenderer = CreateDefaultSubObject<USpriteRenderer>("EffectRenderer");
	//EffectRenderer->SetupAttachment(Root);

	//ScopeRenderer = CreateDefaultSubObject<USpriteRenderer>("ScopeRenderer");
	//ScopeRenderer->SetupAttachment(Root);
}

void ASeaDog::AnimationInit()
{
	CreateAnimation();
	SetAnimationCallback();
}

void ASeaDog::CreateAnimation()
{
	SeaDogRenderer->CreateAnimation(PirateBossAniName::SeaDog_Appear1, "SeaDog_Appear.png", 0.0517f, false, 0, 11);
	SeaDogRenderer->CreateAnimation(PirateBossAniName::SeaDog_Appear2, "SeaDog_Appear.png", 0.057f, false, 12, 13);
	SeaDogRenderer->CreateAnimation(PirateBossAniName::SeaDog_Appear3, "SeaDog_Appear.png", 0.0417f, false, 14, 15);
	SeaDogRenderer->CreateAnimation(PirateBossAniName::SeaDog_Appear4, "SeaDog_Appear.png", 0.0417f, false, 16, 19);
	SeaDogRenderer->CreateAnimation(PirateBossAniName::SeaDog_Appear5, "SeaDog_Appear.png", 0.0417f, false, 20, 21);


	//UEngineSprite::CreateCutting("SeaDog_Appear_Effect.png", 6, 2);
	//UEngineSprite::CreateCutting("SeaDog_Death.png", 8, 1);
	//UEngineSprite::CreateCutting("SeaDog_Death_Effect.png", 5, 2);
	//UEngineSprite::CreateCutting("SeaDog_Move.png", 6, 2);
	//UEngineSprite::CreateCutting("SeaDog_Periscope.png", 10, 5);
}

void ASeaDog::SetAnimationCallback()
{

}

void ASeaDog::ColliderInit()
{

}

void ASeaDog::StateInit()
{
	{
		State.CreateState(PirateBossState::SeaDog_Appear1);
		State.CreateState(PirateBossState::SeaDog_Appear2);
		State.CreateState(PirateBossState::SeaDog_Appear3);
		State.CreateState(PirateBossState::SeaDog_Appear4);
	}

	{
		State.SetStartFunction(PirateBossState::SeaDog_Appear1, [this]()
			{
				SetJumpVec(float4::Up * JumpSpeed);
				SetSpeedVec(float4::Left * Appear1Speed);
				SeaDogRenderer->ChangeAnimation(PirateBossAniName::SeaDog_Appear1);
			});
		State.SetStartFunction(PirateBossState::SeaDog_Appear2, [this]()
			{
				SeaDogRenderer->ChangeAnimation(PirateBossAniName::SeaDog_Appear2);
			});
		State.SetStartFunction(PirateBossState::SeaDog_Appear3, [this]()
			{
				SetSpeedVec(float4::Left * 1000.0f);
				SeaDogRenderer->ChangeAnimation(PirateBossAniName::SeaDog_Appear3);
			});
		State.SetStartFunction(PirateBossState::SeaDog_Appear4, [this]()
			{
				SeaDogRenderer->ChangeAnimation(PirateBossAniName::SeaDog_Appear4);
			});
	}

	{
		State.SetUpdateFunction(PirateBossState::SeaDog_Appear1, std::bind(&ASeaDog::Appear_Step1, this, std::placeholders::_1));
		State.SetUpdateFunction(PirateBossState::SeaDog_Appear2, [this](float)
			{
				if (true == SeaDogRenderer->IsCurAnimationEnd())
				{
					State.ChangeState(PirateBossState::SeaDog_Appear3);
					return;
				}
			});
		State.SetUpdateFunction(PirateBossState::SeaDog_Appear3, std::bind(&ASeaDog::Appear_Step2, this, std::placeholders::_1));
		State.SetUpdateFunction(PirateBossState::SeaDog_Appear4, [this](float)
			{
				if (true == SeaDogRenderer->IsCurAnimationEnd())
				{
					return;
				}
			});
	}

	{
		State.SetEndFunction(PirateBossState::SeaDog_Appear1, [this]()
			{
				SetJumpVec(float4::Zero);
				SetSpeedVec(float4::Zero);
				SetGravityVec(float4::Zero);
			});
		State.SetEndFunction(PirateBossState::SeaDog_Appear3, [this]()
			{
				SetSpeedVec(float4::Zero);
			});
	}

	State.ChangeState(PirateBossState::SeaDog_Appear1);
}

void ASeaDog::CalGravityVec(float _DeltaTime)
{
	float4 Pos = GetActorLocation();
	Pos.Y = -Pos.Y;

	AddGravityVec(_DeltaTime);
}

void ASeaDog::Appear_Step1(float _DeltaTime)
{
	float4 Pos = GetActorLocation();
	Pos.Y = -Pos.Y + PixelCheckOffset;

	if (FirstAppearXBoundary >= Pos.X && true == PixelCheck(Pos, Color8Bit::Black))
	{
		State.ChangeState(PirateBossState::SeaDog_Appear2);
		return;
	}

	CalGravityVec(_DeltaTime);
	ResultMovementUpdate(_DeltaTime);
}

void ASeaDog::Appear_Step2(float _DeltaTime)
{
	if (true == SeaDogRenderer->IsCurAnimationEnd())
	{
		State.ChangeState(PirateBossState::SeaDog_Appear4);
		return;
	}

	ResultMovementUpdate(_DeltaTime);
}