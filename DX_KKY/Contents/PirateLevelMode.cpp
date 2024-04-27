﻿#include "PreCompile.h"
#include <EngineCore/Camera.h>

#include "PirateLevelMode.h"
#include "PirateLevelMap.h"

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
	CreateObject();
	GetWorld()->GetLastTarget()->AddEffect<UBlurEffect>();
}

void APirateLevelMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void APirateLevelMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);

	DeleteObject();
}

void APirateLevelMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	ObjectInit();

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

void APirateLevelMode::CreateObject()
{
	Camera = GetWorld()->GetMainCamera();

	Map = GetWorld()->SpawnActor<APirateLevelMap>("Map", EActorType::Map);
}

void APirateLevelMode::ObjectInit()
{
	Camera->SetActorLocation(UContentsValue::ContentsCameraInitPos);

	Map->SetActorLocation(float4(640.0f, -360.0f, 0.0f));

	Player = GetWorld()->SpawnActor<APlayer>("Player", EActorType::Player);
	Player->SetActorLocation(FVector{ 640.0f, -400.0f, 100.0f });
}

void APirateLevelMode::DeleteObject()
{
	Player->Destroy();
	Player = nullptr;

	Map->ReleaseColMapTexInfo();
}