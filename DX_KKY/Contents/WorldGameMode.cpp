#include "PreCompile.h"
#include <EngineCore/Camera.h>

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

	OldFilm = GetWorld()->SpawnActor<AOldFilmEffect>("OldFilmEffect", static_cast<int>(EActorType::FilmEffect));
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

	// 콜리젼 맵을 가져와서 ContentsValue 클래스에 정보 저장
	UContentsValue::ColMapTexture = UEngineTexture::FindRes(WCMap->GetName());
	float4 ColMapScale = UContentsValue::ColMapTexture->GetScale();

	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(UContentsValue::WorldMapCameraInitValue);

	UICamera = GetWorld()->GetMainCamera();
	UICamera->SetActorLocation(UContentsValue::WorldMapCameraInitValue);


	OldFilm->AddActorLocation(FVector{ UContentsValue::WorldMapPlayerXInitValue, UContentsValue::WorldMapPlayerYInitValue, 0.0f });
	WPlayer->AddActorLocation(FVector{ UContentsValue::WorldMapPlayerXInitValue, UContentsValue::WorldMapPlayerYInitValue, 100.0f });
	MapLayer->AddActorLocation(FVector{ ColMapScale.hX(), -ColMapScale.hY(), 50.0f});
	WMap->AddActorLocation(FVector{ ColMapScale.hX(), -ColMapScale.hY(), 200.0f });
	WCMap->AddActorLocation(FVector{ ColMapScale.hX(), -ColMapScale.hY(), 300.0f });
}

void AWorldGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	CameraMove(_DeltaTime);
}

void AWorldGameMode::CameraMove(float _DeltaTime)
{
	FVector PlayerPos = AWorldPlayer::GetMainPlayer()->GetActorLocation();
	PlayerPos.Z = 0.0f;
	FVector CameraPos = UICamera->GetActorLocation();
	CameraPos.Z = 0.0f;

	FVector ChasePlayerVector = PlayerPos - CameraPos;

	if (1.0f >= ChasePlayerVector.Size3D())
	{
		return;
	}

	UICamera->AddActorLocation(ChasePlayerVector.Normalize3DReturn() * _DeltaTime * 300.0f);
	OldFilm->AddActorLocation(ChasePlayerVector.Normalize3DReturn() * _DeltaTime * 300.0f);
}