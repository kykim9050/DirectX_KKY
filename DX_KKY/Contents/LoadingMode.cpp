#include "PreCompile.h"

#include "LoadingMode.h"
#include "LoadActor.h"

ALoadingMode::ALoadingMode()
{

}

ALoadingMode::~ALoadingMode()
{
}

void ALoadingMode::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetLastTarget()->AddEffect<UBlurEffect>();
}

void ALoadingMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void ALoadingMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);

	ReleaseActor();
}

void ALoadingMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	CreateActor();
}

void ALoadingMode::CreateActor()
{
	OldFilm = CreateWidget<UImage>(GetWorld(), "OldFilm");
	OldFilm->AddToViewPort(ERenderingOrder::OldFilmEffect);
	OldFilm->CreateAnimation(GAniName::OldFilmAni, GSpriteName::OldFilm, 0.05f);
	OldFilm->SetScale(GEngine->EngineWindow.GetWindowScale());
	OldFilm->ChangeAnimation(GAniName::OldFilmAni);

	LoadActor = GetWorld()->SpawnActor<ALoadActor>("LoadActor");

	Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(UContentsValue::ContentsCameraInitPos);
}

void ALoadingMode::ReleaseActor()
{
	if (nullptr != Camera)
	{
		Camera->Destroy();
		Camera = nullptr;
	}

	if (nullptr != LoadActor)
	{
		LoadActor->Destroy();
		LoadActor = nullptr;
	}
}