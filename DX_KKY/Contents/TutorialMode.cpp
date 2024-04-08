#include "PreCompile.h"
#include <EngineCore/Camera.h>

#include "TutorialMode.h"
#include "Player.h"
#include "TutorialMap.h"
#include "MapSubObject.h"

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

	std::shared_ptr<AActor> Player = GetWorld()->SpawnActor<APlayer>("Player");
	std::shared_ptr<AActor>	TutorialMap = GetWorld()->SpawnActor<ATutorialMap>("TutorialMap");
	std::shared_ptr<AActor> BackScreen = GetWorld()->SpawnActor<AMapSubObject>("BackScreen");


	Player->AddActorLocation(FVector{ 0.0f, 0.0f, 0.0f });
	TutorialMap->AddActorLocation(FVector{ 0.0f, 0.0f, 100.0f });
	BackScreen->AddActorLocation(FVector{ 0.0f, 0.0f, 200.0f });

}


void ATutorialMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);


}