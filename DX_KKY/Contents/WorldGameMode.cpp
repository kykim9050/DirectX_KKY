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

	Camera = GetWorld()->GetMainCamera();
	OldFilm = GetWorld()->SpawnActor<AOldFilmEffect>("OldFilmEffect", static_cast<int>(EActorType::FilmEffect));
	std::shared_ptr<AWorldPlayer> WPlayer = GetWorld()->SpawnActor<AWorldPlayer>("WorldPlayer", static_cast<int>(EActorType::Player));
	std::shared_ptr<AMapBase> MapLayer = GetWorld()->SpawnActor<AMapBase>("MapLayer", static_cast<int>(EActorType::BackGroundSubStaticObject));
	std::shared_ptr<AMapBase> WorldMap = GetWorld()->SpawnActor<AMapBase>("WorldMap", static_cast<int>(EActorType::Map));
	std::shared_ptr<AMapBase> WorldCollisionMap = GetWorld()->SpawnActor<AMapBase>("WorldCollisionMap", static_cast<int>(EActorType::Map));

	MapLayer->SetMapFile("WorldMap_Layer.png");
	WorldMap->SetMapFile("WorldMap.png");
	WorldCollisionMap->SetMapFile("WorldMap_PixelCheck.png");
	MapLayer->SetAutoScale();
	WorldMap->SetAutoScale();
	WorldCollisionMap->SetAutoScale();

	// 콜리젼 맵을 가져와서 ContentsValue 클래스에 정보 저장
	UContentsValue::ColMapTexture = UEngineTexture::FindRes(WorldCollisionMap->GetName());
	float4 ColMapScale = UContentsValue::ColMapTexture->GetScale();

	// OldFilm, WPlayer는 오더링 고정
	MapLayer->SetOrdering(ERenderingOrder::FrontLayer);
	WorldMap->SetOrdering(ERenderingOrder::BackLayer);
	WorldCollisionMap->SetOrdering(ERenderingOrder::CollisionLayer);

	Camera->SetActorLocation(UContentsValue::WorldMapCameraInitValue);
	OldFilm->AddActorLocation(FVector{ UContentsValue::WorldMapPlayerXInitValue, UContentsValue::WorldMapPlayerYInitValue, 0.0f });
	WPlayer->AddActorLocation(FVector{ UContentsValue::WorldMapPlayerXInitValue, UContentsValue::WorldMapPlayerYInitValue, 100.0f });
	MapLayer->AddActorLocation(FVector{ ColMapScale.hX(), -ColMapScale.hY(), 50.0f });
	WorldMap->AddActorLocation(FVector{ ColMapScale.hX(), -ColMapScale.hY(), 200.0f });
	WorldCollisionMap->AddActorLocation(FVector{ ColMapScale.hX(), -ColMapScale.hY(), 300.0f });
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
	FVector CameraPos = Camera->GetActorLocation();
	CameraPos.Z = 0.0f;

	FVector ChasePlayerVector = PlayerPos - CameraPos;

	if (1.0f >= ChasePlayerVector.Size3D())
	{
		return;
	}

	Camera->AddActorLocation(ChasePlayerVector.Normalize3DReturn() * _DeltaTime * 300.0f);
	OldFilm->AddActorLocation(ChasePlayerVector.Normalize3DReturn() * _DeltaTime * 300.0f);
}