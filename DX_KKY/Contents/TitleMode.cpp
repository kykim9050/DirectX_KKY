#include "PreCompile.h"
#include <EngineCore/Camera.h>

#include "TitleMode.h"
#include "TitleLogo.h"
#include "TitleAnimation.h"
#include "OldFilmEffect.h"
#include "ContentsEnumClass.h"

ATitleMode::ATitleMode() 
{
	InputOn();
}

ATitleMode::~ATitleMode()
{
}

void ATitleMode::BeginPlay()
{
	Super::BeginPlay();

	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(0.0f, 0.0f, UContentsValue::CameraInitZValue));

	std::shared_ptr<ATitleAnimation> TitleAni = GetWorld()->SpawnActor<ATitleAnimation>("TitleAnimation", static_cast<int>(EActorType::BackGroundAnimation));
	std::shared_ptr<ATitleLogo> TitleLogo = GetWorld()->SpawnActor<ATitleLogo>("TitleLogo", static_cast<int>(EActorType::BackGroundSubStaticObject));
	
	std::shared_ptr<AActor> OldFilm = GetWorld()->SpawnActor<AOldFilmEffect>("TitleOldFilmEffect", static_cast<int>(EActorType::FilmEffect));
}

void ATitleMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

}

void ATitleMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}

void ATitleMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

}