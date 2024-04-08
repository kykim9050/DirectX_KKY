#include "PreCompile.h"
#include <EngineCore/Camera.h>

#include "TutorialMode.h"
#include "Player.h"
#include "TutorialMap.h"

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

	GetWorld()->SpawnActor<APlayer>("Player");
	GetWorld()->SpawnActor<ATutorialMap>("TutorialMap");
}

void ATutorialMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);


}