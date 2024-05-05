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
	//StateInit();

	{
		SeaDogRenderer->ChangeAnimation(PirateBossAniName::SeaDog_Appear1);
	}
}

void ASeaDog::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	//State.Update(_DeltaTime);
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
	SeaDogRenderer->CreateAnimation(PirateBossAniName::SeaDog_Appear1, "SeaDog_Appear.png", 0.0417f, false, 0, 11);
	SeaDogRenderer->CreateAnimation(PirateBossAniName::SeaDog_Appear2, "SeaDog_Appear.png", 0.0417f, false, 12, 13);
	SeaDogRenderer->CreateAnimation(PirateBossAniName::SeaDog_Appear3, "SeaDog_Appear.png", 0.0417f, false, 14, 15);
	SeaDogRenderer->CreateAnimation(PirateBossAniName::SeaDog_Appear4, "SeaDog_Appear.png", 0.0417f, false, 16, 19);
	SeaDogRenderer->CreateAnimation(PirateBossAniName::SeaDog_Appear5, "SeaDog_Appear.png", 0.0417f, false, 20, 21);


	//	UEngineSprite::CreateCutting("SeaDog_Appear.png", 11, 2);
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

}