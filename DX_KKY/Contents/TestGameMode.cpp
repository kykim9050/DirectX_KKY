#include "PreCompile.h"
#include <EngineCore/Camera.h>
#include "Player.h"

#include "TestGameMode.h"
#include "ContentsEnumClass.h"
#include "WorldDust.h"

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

	//GetWorld()->SpawnActor<APlayer>("Player", static_cast<int>(EActorType::Player));
	std::shared_ptr<AWorldDust> Dust = GetWorld()->SpawnActor<AWorldDust>("WorldDust", static_cast<int>(EActorType::Dust));

	Dust->SetActorLocation(FVector(0.0f, 0.0f, 100.0f));
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