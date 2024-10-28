#include "PreCompile.h"
#include <EngineCore/Camera.h>
#include "Player.h"

#include "TestGameMode.h"
#include "WorldDust.h"
#include "WorldGameMode.h"
#include "MapSubObject.h"
#include "WorldPlayer.h"
#include "OldFilmEffect.h"
#include "TitleAnimation.h"
#include "TitleLogo.h"

ATestGameMode::ATestGameMode()
{
}

ATestGameMode::~ATestGameMode()
{
}

void ATestGameMode::BeginPlay()
{
	Super::BeginPlay();
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
		MsgBoxAssert("�ùٸ��� ���� ��ĳ���� �����Դϴ�.");
		return;
	}

	if (nullptr == WCMap)
	{
		MsgBoxAssert("�ùٸ��� ���� ��ĳ���� �����Դϴ�.");
		return;
	}
#endif // _DEBUG

	WMap->SetMapFile("WorldMap.png");
	WMap->SetAutoScale();

	WCMap->SetMapFile("WorldMap_PixelCheck.png");
	WCMap->SetAutoScale();

	MapLayer->SetMapSubObject("WorldMap_Layer.png");
	MapLayer->SetMapSubObjectScale(WMap->GetMapScale());

	// �ݸ��� ���� �����ͼ� ContentsValue Ŭ������ ���� ����
	UContentsValue::ColMapTexture = UEngineTexture::FindRes(WCMap->GetName());
	float4 ColMapScale = UContentsValue::ColMapTexture->GetScale();

	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(UContentsValue::WorldMapCameraInitValue);

	OldFilm->AddActorLocation(FVector{ UContentsValue::WorldMapPlayerXInitValue, UContentsValue::WorldMapPlayerYInitValue, 0.0f });
	WPlayer->AddActorLocation(FVector{ UContentsValue::WorldMapPlayerXInitValue, UContentsValue::WorldMapPlayerYInitValue, 100.0f });
	MapLayer->AddActorLocation(FVector{ ColMapScale.hX(), -ColMapScale.hY(), 50.0f });
	WMap->AddActorLocation(FVector{ ColMapScale.hX(), -ColMapScale.hY(), 200.0f });
	WCMap->AddActorLocation(FVector{ ColMapScale.hX(), -ColMapScale.hY(), 300.0f });


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