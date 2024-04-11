#include "PreCompile.h"
#include <EngineCore/Camera.h>

#include "TutorialMode.h"
#include "Player.h"
#include "TutorialMap.h"
#include "MapSubObject.h"
#include "OldFilmEffect.h"
#include "ContentsEnumClass.h"

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

	std::shared_ptr<AActor> OldFilm = GetWorld()->SpawnActor<AOldFilmEffect>("OldFilmEffect", static_cast<int>(EActorType::FilmEffect));
	std::shared_ptr<AMapSubObject> FrontScreen = GetWorld()->SpawnActor<AMapSubObject>("FrontScreen", static_cast<int>(EActorType::BackGroundSubStaticObject));
	std::shared_ptr<APlayer> Player = GetWorld()->SpawnActor<APlayer>("Player", static_cast<int>(EActorType::Player));
	std::shared_ptr<AActor>	TutorialMap = GetWorld()->SpawnActor<ATutorialMap>("TutorialMap", static_cast<int>(EActorType::Map));
	std::shared_ptr<AMapSubObject> BackScreen = GetWorld()->SpawnActor<AMapSubObject>("BackScreen", static_cast<int>(EActorType::BackGroundSubStaticObject));

	FVector WindowScale = GEngine->EngineWindow.GetWindowScale();

	FrontScreen->SetMapSubObject("tutorial_room_front_layer_0001.png");
	BackScreen->SetMapSubObject("tutorial_room_back_layer_0001.png");
	FrontScreen->SetMapSubObjectScale(WindowScale);
	BackScreen->SetMapSubObjectScale(WindowScale);


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