#include "PreCompile.h"
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>

#include "LoadActor.h"

ALoadActor::ALoadActor()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");
	SetRoot(Root);

	CreateObject();
}

ALoadActor::~ALoadActor()
{
}

void ALoadActor::BeginPlay()
{
	Super::BeginPlay();

	RendererInit();
	AnimationInit();
}


void ALoadActor::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void ALoadActor::CreateObject()
{
	HourglassRenderer = CreateDefaultSubObject<USpriteRenderer>("HourglassRenderer");
	HourglassRenderer->SetupAttachment(Root);

	BackGroundRenderer = CreateDefaultSubObject<USpriteRenderer>("BackGroundRenderer");
	BackGroundRenderer->SetupAttachment(Root);
}

void ALoadActor::RendererInit()
{
	HourglassRenderer->SetAutoSize(1.0f, true);
	HourglassRenderer->SetOrder(ERenderingOrder::HourGlass);
	HourglassRenderer->SetPosition(GRendererPos::Loading_HourGlass_InitPos);


	BackGroundRenderer->SetScale(GEngine->EngineWindow.GetWindowScale());
	BackGroundRenderer->SetOrder(ERenderingOrder::Iris);
	BackGroundRenderer->SetPosition(GRendererPos::Loading_BackGround_InitPos);
	BackGroundRenderer->SetSprite("Iris", 0);
}

void ALoadActor::AnimationInit()
{
	HourglassRenderer->CreateAnimation(GAniName::Hourglass, "Hourglass", 0.05f);
	HourglassRenderer->ChangeAnimation(GAniName::Hourglass);
}