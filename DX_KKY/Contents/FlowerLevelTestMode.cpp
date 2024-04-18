#include "PreCompile.h"
#include <EngineCore/Camera.h>

#include "FlowerLevelTestMode.h"


#include "OldFilmEffect.h"
#include "Player.h"
#include "MapBase.h"
#include "CagneyCarnation.h"

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

	std::shared_ptr<AOldFilmEffect> OldFilm = GetWorld()->SpawnActor<AOldFilmEffect>("OldFilmEffect", static_cast<int>(EActorType::FilmEffect));
	OldFilm->SetActorLocation(FVector{ UContentsValue::ContentsCameraInitXPos, UContentsValue::ContentsCameraInitYPos, 0.0f });

	std::shared_ptr<APlayer> Player = GetWorld()->SpawnActor<APlayer>("Player", EActorType::Player);
	Player->SetActorLocation(FVector{ 640.0f, -400.0f, 100.0f });

	std::shared_ptr<ACagneyCarnation> BossMonster = GetWorld()->SpawnActor<ACagneyCarnation>("BossMonster", EActorType::BossMonster);
	BossMonster->SetActorLocation(FVector{ 1000.0f, -370.0f, 100.0f });

	std::shared_ptr<AMapBase> MapFrontObject = GetWorld()->SpawnActor<AMapBase>("MapFrontObject", EActorType::Map);
	MapFrontObject->SetMapFile("Flower_Background_Front.png");
	MapFrontObject->SetAutoScale();
	MapFrontObject->SetActorLocation(FVector(630.0f, -575.0f, 50.0f));
	MapFrontObject->SetOrdering(ERenderingOrder::FrontLayer);

	std::shared_ptr<AMapBase> Map = GetWorld()->SpawnActor<AMapBase>("Map", EActorType::Map);
	Map->SetMapFile("Flower_Background.png");
	Map->SetAutoScale();
	Map->SetActorLocation(FVector(689.0f, -404.0f, 200.0f));
	Map->SetOrdering(ERenderingOrder::BackLayer);

	std::shared_ptr<AMapBase> BackGroundObject = GetWorld()->SpawnActor<AMapBase>("BackGroundObject", EActorType::Map);
	BackGroundObject->SetMapFile("Flower_Background_Cloud02.png");
	BackGroundObject->SetAutoScale();
	BackGroundObject->SetActorLocation(FVector(700.0f, -233.0f, 300.0f));
	BackGroundObject->SetOrdering(ERenderingOrder::BackLayer2);

	std::shared_ptr<AMapBase> ColMap = GetWorld()->SpawnActor<AMapBase>("ColMap", EActorType::Map);
	ColMap->SetMapFile("Flower_Background_PixelCheck.png");
	ColMap->SetAutoScale();
	ColMap->SetOrdering(ERenderingOrder::CollisionLayer);
	ColMap->SetActorLocation(FVector(640.0f, -360.0f, 400.0f));
	ColMap->SetOrdering(ERenderingOrder::CollisionLayer);
	UContentsValue::ColMapTexture = UEngineTexture::FindRes(ColMap->GetName());

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