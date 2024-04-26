#include "PreCompile.h"

#include "PirateLevelMode.h"

APirateLevelMode::APirateLevelMode()
{
}

APirateLevelMode::~APirateLevelMode()
{
}

void APirateLevelMode::BeginPlay()
{
	Super::BeginPlay();

	WidgetInit();
}

void APirateLevelMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void APirateLevelMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}

void APirateLevelMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	OldFilm->ChangeAnimation(GAniName::OldFilmAni);
	Iris->ChangeAnimation(GAniName::IrisAni);
}

void APirateLevelMode::WidgetInit()
{
	OldFilm = CreateWidget<UImage>(GetWorld(), "OldFilm");
	OldFilm->AddToViewPort(ERenderingOrder::OldFilmEffect);
	OldFilm->CreateAnimation(GAniName::OldFilmAni, GSpriteName::OldFilm, 0.05f);
	OldFilm->SetPosition(float4(0.0f, 0.0f, 0.0f));
	OldFilm->SetScale(GEngine->EngineWindow.GetWindowScale());

	Iris = CreateWidget<UImage>(GetWorld(), "Iris");
	Iris->AddToViewPort(ERenderingOrder::Iris);
	Iris->CreateAnimation(GAniName::IrisAni, GSpriteName::Iris, 0.034f, false);
	Iris->SetPosition(float4(0.0f, 0.0f, 0.0f));
	Iris->SetScale(GEngine->EngineWindow.GetWindowScale());
}