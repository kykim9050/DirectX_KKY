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

	Camera = GetWorld()->GetMainCamera();
	OldFilm = GetWorld()->SpawnActor<AOldFilmEffect>("OldFilmEffect", static_cast<int>(EActorType::FilmEffect));
	GetWorld()->GetLastTarget()->AddEffect<UBlurEffect>();
}

void AEndingMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

}

void AEndingMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);

	EndingAni->Destroy();
	EndingAni = nullptr;

	BGMPlayer.Off();
}

void AEndingMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	EndingAni = GetWorld()->SpawnActor<AEndingAnimation>("EndingAnimation", static_cast<int>(EActorType::BackGroundAnimation));
	Camera->SetActorLocation(FVector(0.0f, 0.0f, UContentsValue::CameraInitZValue));

	BGMPlayer = UEngineSound::SoundPlay("Ending_bgm.wav");
	BGMPlayer.Loop();
}
