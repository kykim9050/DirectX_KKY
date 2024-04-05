#include "PreCompile.h"
#include "TitleMode.h"
#include "TitleLogo.h"
#include "TitleAnimation.h"
#include <EngineCore/Camera.h>

ATitleMode::ATitleMode() 
{
}

ATitleMode::~ATitleMode()
{
}

void ATitleMode::BeginPlay()
{
	Super::BeginPlay();

	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(0.0f, 0.0f, -100.0f));
	GetWorld()->SpawnActor<ATitleLogo>("TitleLogo");
	GetWorld()->SpawnActor<ATitleAnimation>("TitleAnimation");
}

void ATitleMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

}

void ATitleMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}

void ATitleMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

}