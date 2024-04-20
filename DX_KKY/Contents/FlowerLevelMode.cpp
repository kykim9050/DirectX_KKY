#include "PreCompile.h"
#include <EngineCore/Camera.h>

#include "FlowerLevelMode.h"


#include "OldFilmEffect.h"
#include "Player.h"
#include "MapBase.h"
#include "CagneyCarnation.h"

//
#include "FXBase.h"
//



AFlowerLevelMode::AFlowerLevelMode()
{
}

AFlowerLevelMode::~AFlowerLevelMode()
{
}

void AFlowerLevelMode::BeginPlay()
{
	Super::BeginPlay();

	Camera = GetWorld()->GetMainCamera();
	OldFilm = GetWorld()->SpawnActor<AOldFilmEffect>("OldFilmEffect", static_cast<int>(EActorType::FilmEffect));
	GetWorld()->GetLastTarget()->AddEffect<UBlurEffect>();
	
	Player = GetWorld()->SpawnActor<APlayer>("Player", EActorType::Player);
	BossMonster = GetWorld()->SpawnActor<ACagneyCarnation>("BossMonster", EActorType::BossMonster);
	MapFrontObject = GetWorld()->SpawnActor<AMapBase>("MapFrontObject", EActorType::Map);
	Map = GetWorld()->SpawnActor<AMapBase>("Map", EActorType::Map);
	BackGroundObject = GetWorld()->SpawnActor<AMapBase>("BackGroundObject", EActorType::Map);
	ColMap = GetWorld()->SpawnActor<AMapBase>("ColMap", EActorType::Map);


	{
		std::shared_ptr<AFXBase> BlueMissile = GetWorld()->SpawnActor<AFXBase>("BlueMissile");
		BlueMissile->FXInit(ERenderingOrder::BossMonsterBackFX2, FFXAniInfo("GatlingMissileBlue", "GatlingMissileBlue", 0.0414f), true);
		BlueMissile->SetActorLocation(FVector(640.0f, -360.0f, 0.0f));

		std::shared_ptr<AFXBase> PurpleMissile = GetWorld()->SpawnActor<AFXBase>("PurpleMissile ");
		PurpleMissile->FXInit(ERenderingOrder::BossMonsterBackFX1, FFXAniInfo("GatlingMissilePurple", "GatlingMissilePurple", 0.0414f), true);
		PurpleMissile->SetActorLocation(FVector(640.0f, -360.0f, 0.0f));
	}
}

void AFlowerLevelMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AFlowerLevelMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);

	UContentsValue::ColMapTexture = nullptr;
}

void AFlowerLevelMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	Camera->SetActorLocation(UContentsValue::ContentsCameraInitPos);
	OldFilm->SetActorLocation(FVector{ UContentsValue::ContentsCameraInitXPos, UContentsValue::ContentsCameraInitYPos, 0.0f });
	Player->SetActorLocation(FVector{ 640.0f, -400.0f, 100.0f });
	BossMonster->SetActorLocation(FVector{ 1380.0f, -680.0f, 100.0f });
	
	MapFrontObject->SetMapFile("Flower_Background_Front.png");
	MapFrontObject->SetAutoScale();
	MapFrontObject->SetActorLocation(FVector(630.0f, -575.0f, 50.0f));
	MapFrontObject->SetOrdering(ERenderingOrder::FrontLayer);
	
	Map->SetMapFile("Flower_Background.png");
	Map->SetAutoScale();
	Map->SetActorLocation(FVector(689.0f, -404.0f, 200.0f));
	Map->SetOrdering(ERenderingOrder::BackLayer);

	BackGroundObject->SetMapFile("Flower_Background_Cloud02.png");
	BackGroundObject->SetAutoScale();
	BackGroundObject->SetActorLocation(FVector(700.0f, -233.0f, 300.0f));
	BackGroundObject->SetOrdering(ERenderingOrder::BackLayer2);

	ColMap->SetMapFile("Flower_Background_PixelCheck.png");
	ColMap->SetAutoScale();
	ColMap->SetOrdering(ERenderingOrder::CollisionLayer);
	ColMap->SetActorLocation(FVector(640.0f, -360.0f, 400.0f));
	ColMap->SetOrdering(ERenderingOrder::CollisionLayer);
	UContentsValue::ColMapTexture = UEngineTexture::FindRes(ColMap->GetName());
}