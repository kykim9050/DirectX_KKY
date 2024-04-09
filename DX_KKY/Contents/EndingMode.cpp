#include "PreCompile.h"
#include <EngineCore/Camera.h>

#include "EndingMode.h"
#include "EndingAnimation.h"
#include "OldFilmEffect.h"
#include "ContentsEnumClass.h"

AEndingMode::AEndingMode()
{
}

AEndingMode::~AEndingMode()
{
}

void AEndingMode::BeginPlay()
{
	Super::BeginPlay();

	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(0.0f, 0.0f, UContentsValue::CameraInitZValue));

	std::shared_ptr<AActor> OldFilm = GetWorld()->SpawnActor<AOldFilmEffect>("OldFilmEffect", static_cast<int>(EActorType::FilmEffect));
	OldFilm->SetOrder(EEndingRenderingOrder::DisplayEffect);

	std::shared_ptr<AEndingAnimation> TitleAni = GetWorld()->SpawnActor<AEndingAnimation>("EndingAnimation", static_cast<int>(EActorType::BackGroundAnimation));
	TitleAni->SetOrder(EEndingRenderingOrder::Animation);
}

void AEndingMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

}

void AEndingMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}

void AEndingMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

}
