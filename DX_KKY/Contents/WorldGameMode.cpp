#include "PreCompile.h"
#include <EngineCore/Camera.h>

#include "ContentsEnumClass.h"
#include "WorldGameMode.h"
#include "MapSubObject.h"
#include "WorldPlayer.h"
#include "OldFilmEffect.h"


AWorldGameMode::AWorldGameMode()
{
}

AWorldGameMode::~AWorldGameMode()
{
}

void AWorldGameMode::BeginPlay()
{
	Super::BeginPlay();

	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(0.0f, 0.0f, UContentsValue::CameraInitZValue));

	std::shared_ptr<AActor> OldFilm = GetWorld()->SpawnActor<AOldFilmEffect>("OldFilmEffect", static_cast<int>(EActorType::FilmEffect));
	std::shared_ptr<AMapSubObject> MapLayer = GetWorld()->SpawnActor<AMapSubObject>("MapLayer", static_cast<int>(EActorType::BackGroundSubStaticObject));
	std::shared_ptr<AActor> WPlayer = GetWorld()->SpawnActor<AWorldPlayer>("WorldPlayer", static_cast<int>(EActorType::Player));
	std::shared_ptr<AActor>	WorldMap = GetWorld()->SpawnActor<AMapBase>("WorldMap", static_cast<int>(EActorType::Map));
	std::shared_ptr<AActor> WorldCollisionMap = GetWorld()->SpawnActor<AMapBase>("WorldCollisionMap", static_cast<int>(EActorType::Map));


	std::shared_ptr<AMapBase> WMap = std::dynamic_pointer_cast<AMapBase>(WorldMap);
	std::shared_ptr<AMapBase> WCMap = std::dynamic_pointer_cast<AMapBase>(WorldCollisionMap);

#ifdef _DEBUG
	if (nullptr == WMap)
	{
		MsgBoxAssert("올바르지 못한 업캐스팅 형식입니다.");
		return;
	}

	if (nullptr == WCMap)
	{
		MsgBoxAssert("올바르지 못한 업캐스팅 형식입니다.");
		return;
	}
#endif // _DEBUG

	WMap->SetMapFile("WorldMap.png");
	WMap->SetAutoScale();

	WCMap->SetMapFile("WorldMap_PixelCheck.png");
	WCMap->SetAutoScale();

	MapLayer->SetMapSubObject("WorldMap_Layer.png");
	MapLayer->SetMapSubObjectScale(WMap->GetMapScale());

	

	OldFilm->AddActorLocation(FVector{ 0.0f, 0.0f, 0.0f });
	MapLayer->AddActorLocation(FVector{ 0.0f, 0.0f, 50.0f });
	WPlayer->AddActorLocation(FVector{ 0.0f, 0.0f, 100.0f });
	WorldMap->AddActorLocation(FVector{ 0.0f, 0.0f, 200.0f });
	WorldCollisionMap->AddActorLocation(FVector{ 0.0f, 0.0f, 300.0f });
}

void AWorldGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}