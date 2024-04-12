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
	Camera->SetActorLocation(FVector(0.0f, 0.0f, UContentsValue::CameraInitZValue));

	//std::shared_ptr<AMapBase> FrontScreen = GetWorld()->SpawnActor<AMapBase>("FrontScreen", static_cast<int>(EActorType::BackGroundSubStaticObject));
	std::shared_ptr<APlayer> Player = GetWorld()->SpawnActor<APlayer>("Player", static_cast<int>(EActorType::Player));
	//std::shared_ptr<AMapBase> BackScreen = GetWorld()->SpawnActor<AMapBase>("BackScreen", static_cast<int>(EActorType::BackGroundSubStaticObject));
	std::shared_ptr<AMapBase> Map = GetWorld()->SpawnActor<AMapBase>("TutorialMap", static_cast<int>(EActorType::Map));
	std::shared_ptr<AMapBase> ColMap = GetWorld()->SpawnActor<AMapBase>("TutorialColMap", static_cast<int>(EActorType::Map));
	std::shared_ptr<AOldFilmEffect> OldFilm = GetWorld()->SpawnActor<AOldFilmEffect>("OldFilmEffect", static_cast<int>(EActorType::FilmEffect));

	FVector WindowScale = GEngine->EngineWindow.GetWindowScale();

	//FrontScreen->SetMapFile("tutorial_room_front_layer_0001.png");
	//BackScreen->SetMapFile("tutorial_room_back_layer_0001.png");
	Map->SetMapFile("tutorial_object.png");
	ColMap->SetMapFile("TutorialScene_Background_PixelCheck.png");
	//FrontScreen->SetMapScale(WindowScale);
	//BackScreen->SetMapScale(WindowScale);
	Map->SetAutoScale();
	ColMap->SetAutoScale();

	// OldFilmEffect, Player는 랜더러 오더링이 정해져 있음
	Map->SetOrdering(ERenderingOrder::StaticObject);
	//FrontScreen->SetOrdering(ERenderingOrder::FrontLayer);
	//BackScreen->SetOrdering(ERenderingOrder::BackLayer);
	ColMap->SetOrdering(ERenderingOrder::CollisionLayer);

	OldFilm->SetActorLocation(FVector{ 0.0f, 0.0f, 0.0f });
	Player->SetActorLocation(FVector{ 0.0f, 0.0f, 200.0f });
	Map->SetActorLocation(FVector{ 0.0f, 0.0f, 300.0f });
	//FrontScreen->SetActorLocation(FVector{ 0.0f, 0.0f, 100.0f });
	//BackScreen->SetActorLocation(FVector{ 0.0f, 0.0f, 400.0f });
	ColMap->SetActorLocation(FVector{ 0.0f, 0.0f, 500.0f });
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