#include "PreCompile.h"
#include <EngineCore/Camera.h>

#include "TutorialMode.h"
#include "MapBase.h"
#include "Player.h"
#include "OldFilmEffect.h"

ATutorialMode::ATutorialMode()
{
}

ATutorialMode::~ATutorialMode()
{
}

void ATutorialMode::BeginPlay()
{
	Super::BeginPlay();

	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(0.0f, 0.0f, UContentsValue::CameraInitZValue));

	std::shared_ptr<AMapBase> FrontScreen = GetWorld()->SpawnActor<AMapBase>("FrontScreen", static_cast<int>(EActorType::BackGroundSubStaticObject));
	std::shared_ptr<APlayer> Player = GetWorld()->SpawnActor<APlayer>("Player", static_cast<int>(EActorType::Player));
	std::shared_ptr<AMapBase> BackScreen = GetWorld()->SpawnActor<AMapBase>("BackScreen", static_cast<int>(EActorType::BackGroundSubStaticObject));
	std::shared_ptr<AMapBase> TutorialMap = GetWorld()->SpawnActor<AMapBase>("TutorialMap", static_cast<int>(EActorType::Map));
	std::shared_ptr<AOldFilmEffect> OldFilm = GetWorld()->SpawnActor<AOldFilmEffect>("OldFilmEffect", static_cast<int>(EActorType::FilmEffect));

	FVector WindowScale = GEngine->EngineWindow.GetWindowScale();

	FrontScreen->SetMapFile("tutorial_room_front_layer_0001.png");
	BackScreen->SetMapFile("tutorial_room_back_layer_0001.png");
	TutorialMap->SetMapFile("tutorial_object.png");
	FrontScreen->SetMapScale(WindowScale);
	BackScreen->SetMapScale(WindowScale);
	TutorialMap->SetAutoScale();

	// OldFilmEffect, Player는 랜더러 오더링이 정해져 있음
	FrontScreen->SetOrdering(ERenderingOrder::FrontLayer);
	TutorialMap->SetOrdering(ERenderingOrder::StaticObject);
	BackScreen->SetOrdering(ERenderingOrder::BackLayer1);


	OldFilm->AddActorLocation(FVector{ 0.0f, 0.0f, 0.0f });
	FrontScreen->AddActorLocation(FVector{ 0.0f, 0.0f, 100.0f });
	Player->AddActorLocation(FVector{ 0.0f, 0.0f, 200.0f });
	TutorialMap->AddActorLocation(FVector{ 0.0f, 0.0f, 300.0f });
	BackScreen->AddActorLocation(FVector{ 0.0f, 0.0f, 400.0f });

}


void ATutorialMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);


}