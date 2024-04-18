#include "PreCompile.h"
#include <EngineCore/Camera.h>

#include "FlowerLevelTestMode.h"


#include "OldFilmEffect.h"
#include "Player.h"
#include "MapBase.h"

AFlowerLevelTestMode::AFlowerLevelTestMode()
{
}

AFlowerLevelTestMode::~AFlowerLevelTestMode()
{
}

void AFlowerLevelTestMode::BeginPlay()
{
	Super::BeginPlay();

	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(UContentsValue::ContentsCameraInitPos);

	//std::shared_ptr<AOldFilmEffect> OldFilm = GetWorld()->SpawnActor<AOldFilmEffect>("OldFilmEffect", static_cast<int>(EActorType::FilmEffect));
	//OldFilm->SetActorLocation(FVector{ UContentsValue::ContentsCameraInitXPos, UContentsValue::ContentsCameraInitYPos, 0.0f });

	FVector WindowScale = GEngine->EngineWindow.GetWindowScale();

	std::shared_ptr<AMapBase> ColMap = GetWorld()->SpawnActor<AMapBase>("ColMap", EActorType::Map);
	ColMap->SetMapFile("Flower_Background_PixelCheck.png");
	ColMap->SetAutoScale();
	ColMap->SetOrdering(ERenderingOrder::CollisionLayer);
	ColMap->SetActorLocation(FVector(640.0f, -360.0f, 200.0f));
	UContentsValue::ColMapTexture = UEngineTexture::FindRes(ColMap->GetName());
	

	std::shared_ptr<APlayer> Player = GetWorld()->SpawnActor<APlayer>("Player", EActorType::Player);
	Player->SetActorLocation(FVector{ 640.0f, -360.0f, 100.0f });
}

void AFlowerLevelTestMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AFlowerLevelTestMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}

void AFlowerLevelTestMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);
}