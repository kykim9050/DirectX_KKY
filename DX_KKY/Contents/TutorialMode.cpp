#include "PreCompile.h"
#include <EngineCore/Camera.h>

#include "TutorialMode.h"
#include "Player.h"
#include "TutorialMap.h"
#include "MapSubObject.h"
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
	Camera->SetActorLocation(FVector(0.0f, 0.0f, -100.0f));

	std::shared_ptr<AActor> OldFilm = GetWorld()->SpawnActor<AOldFilmEffect>("OldFilmEffect");
	std::shared_ptr<AMapSubObject> FrontScreen = GetWorld()->SpawnActor<AMapSubObject>("FrontScreen");
	std::shared_ptr<AActor> Player = GetWorld()->SpawnActor<APlayer>("Player");
	std::shared_ptr<AActor>	TutorialMap = GetWorld()->SpawnActor<ATutorialMap>("TutorialMap");
	std::shared_ptr<AMapSubObject> BackScreen = GetWorld()->SpawnActor<AMapSubObject>("BackScreen");
	
	FVector WindowScale = GEngine->EngineWindow.GetWindowScale();

	FrontScreen->SetMapSubObject("tutorial_room_front_layer_0001.png");
	BackScreen->SetMapSubObject("tutorial_room_back_layer_0001.png");
	FrontScreen->SetMapSubObjectScale(WindowScale);
	BackScreen->SetMapSubObjectScale(WindowScale);

	OldFilm->AddActorLocation(FVector{ 0.0f, 0.0f, 0.0f });
	FrontScreen->AddActorLocation(FVector{ 0.0f, 0.0f, 50.0f });
	Player->AddActorLocation(FVector{ 0.0f, 0.0f, 100.0f });
	TutorialMap->AddActorLocation(FVector{ 0.0f, 0.0f, 200.0f });
	BackScreen->AddActorLocation(FVector{ 0.0f, 0.0f, 300.0f });

}


void ATutorialMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);


}