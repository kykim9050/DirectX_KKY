#include "PreCompile.h"
#include <EngineCore/Camera.h>
#include "Player.h"

#include "TestGameMode.h"
#include "WorldDust.h"
#include "WorldGameMode.h"
#include "MapSubObject.h"
#include "WorldPlayer.h"
#include "OldFilmEffect.h"
#include "TitleAnimation.h"
#include "TitleLogo.h"

ATestGameMode::ATestGameMode()
{
}

ATestGameMode::~ATestGameMode()
{
}

void ATestGameMode::BeginPlay()
{
	Super::BeginPlay();

	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	

	//std::shared_ptr<AMapBase> FrontScreen = GetWorld()->SpawnActor<AMapBase>("FrontScreen", static_cast<int>(EActorType::BackGroundSubStaticObject));
	//std::shared_ptr<AMapBase> BackScreen = GetWorld()->SpawnActor<AMapBase>("BackScreen", static_cast<int>(EActorType::BackGroundSubStaticObject));
	std::shared_ptr<AOldFilmEffect> OldFilm = GetWorld()->SpawnActor<AOldFilmEffect>("OldFilmEffect", static_cast<int>(EActorType::FilmEffect));
	std::shared_ptr<AMapBase> Map = GetWorld()->SpawnActor<AMapBase>("TutorialMap", static_cast<int>(EActorType::Map));
	std::shared_ptr<APlayer> Player = GetWorld()->SpawnActor<APlayer>("Player", static_cast<int>(EActorType::Player));
	std::shared_ptr<AMapBase> ColMap = GetWorld()->SpawnActor<AMapBase>("TutorialColMap", static_cast<int>(EActorType::Map));

	FVector WindowScale = GEngine->EngineWindow.GetWindowScale();

	//FrontScreen->SetMapFile("tutorial_room_front_layer_0001.png");
	//BackScreen->SetMapFile("tutorial_room_back_layer_0001.png");
	//FrontScreen->SetMapScale(WindowScale);
	//BackScreen->SetMapScale(WindowScale);

	Map->SetMapFile("tutorial_object.png");
	Map->SetAutoScale();
	ColMap->SetMapFile("TutorialScene_Background_PixelCheck.png");
	ColMap->SetAutoScale();

	UContentsValue::ColMapTexture = UEngineTexture::FindRes(ColMap->GetName());
	float4 ColMapScale = UContentsValue::ColMapTexture->GetScale();


	// OldFilmEffect, Player는 랜더러 오더링이 정해져 있음
	//FrontScreen->SetOrdering(ERenderingOrder::FrontLayer);
	//BackScreen->SetOrdering(ERenderingOrder::BackLayer);
	Map->SetOrdering(ERenderingOrder::StaticObject);
	ColMap->SetOrdering(ERenderingOrder::CollisionLayer);

	//FrontScreen->SetActorLocation(FVector{ 0.0f, 0.0f, 100.0f });
	//BackScreen->SetActorLocation(FVector{ 0.0f, 0.0f, 400.0f });
	OldFilm->SetActorLocation(FVector{ 640.0f, -360.0f, 0.0f });
	Map->SetActorLocation(FVector{ 3100.0f, -405.0f, 300.0f });
	Camera->SetActorLocation(FVector(640.0f, -360.0f, UContentsValue::CameraInitZValue));
	Player->SetActorLocation(FVector{ 640.0f, -360.0f, 200.0f });
	ColMap->SetActorLocation(FVector{ 3100.0f, -405.0f, 500.0f });




	//Camera->SetActorLocation(UContentsValue::WorldMapCameraInitValue);
	//OldFilm->AddActorLocation(FVector{ UContentsValue::WorldMapPlayerXInitValue, UContentsValue::WorldMapPlayerYInitValue, 0.0f });
	//WPlayer->AddActorLocation(FVector{ UContentsValue::WorldMapPlayerXInitValue, UContentsValue::WorldMapPlayerYInitValue, 100.0f });
	//MapLayer->AddActorLocation(FVector{ ColMapScale.hX(), -ColMapScale.hY(), 50.0f });
	//WorldMap->AddActorLocation(FVector{ ColMapScale.hX(), -ColMapScale.hY(), 200.0f });
	//WorldCollisionMap->AddActorLocation(FVector{ ColMapScale.hX(), -ColMapScale.hY(), 300.0f });

}

void ATestGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void ATestGameMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}

void ATestGameMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

}