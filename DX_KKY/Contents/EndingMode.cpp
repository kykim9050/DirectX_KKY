#include "PreCompile.h"
#include "EndingMode.h"
#include <EngineCore/Camera.h>
#include "EndingAnimation.h"

AEndingMode::AEndingMode()
{
}

AEndingMode::~AEndingMode()
{
}

void AEndingMode::BeginPlay()
{
	Super::BeginPlay();

	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(0.0f, 0.0f, -100.0f));

	std::shared_ptr<AEndingAnimation> TitleAni = GetWorld()->SpawnActor<AEndingAnimation>("EndingAnimation");
}

void AEndingMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

}

void AEndingMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}

void AEndingMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

}
