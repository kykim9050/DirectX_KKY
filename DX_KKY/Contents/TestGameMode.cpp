#include "PreCompile.h"
#include <EngineCore/Camera.h>
#include "Player.h"

#include "TestGameMode.h"
#include "WorldDust.h"
#include "WorldGameMode.h"
#include "MapBase.h"
#include "WorldPlayer.h"
#include "OldFilmEffect.h"
#include "TitleAnimation.h"
#include "TitleLogo.h"
#include "ContentsCamera.h"


ATestGameMode::ATestGameMode()
{
}

ATestGameMode::~ATestGameMode()
{
}

void ATestGameMode::BeginPlay()
{
	Super::BeginPlay();

	std::shared_ptr<UContentsCamera> Camera = GetWorld()->SpawnActor< UContentsCamera>("StageCamera", EActorType::ContentsCamera);
	std::shared_ptr<APlayer> Player = GetWorld()->SpawnActor<APlayer>("Player", EActorType::Player);
	//std::shared_ptr<AMapBase> Map = GetWorld()->SpawnActor<AMapBase>("TutorialMap", EActorType::Map);
	std::shared_ptr<AMapBase> ColMap = GetWorld()->SpawnActor<AMapBase>("TutorialColMap", EActorType::Map);

	FVector WindowScale = GEngine->EngineWindow.GetWindowScale();

	//Map->SetMapFile("tutorial_object.png");
	//Map->SetAutoScale();
	ColMap->SetMapFile("TutorialScene_Background_PixelCheck.png");
	ColMap->SetAutoScale();

	UContentsValue::ColMapTexture = UEngineTexture::FindRes(ColMap->GetName());
	float4 ColMapScale = UContentsValue::ColMapTexture->GetScale();


	//Map->SetOrdering(ERenderingOrder::StaticObject);
	ColMap->SetOrdering(ERenderingOrder::CollisionLayer);

	//Map->SetActorLocation(FVector{ 3100.0f, -405.0f, 300.0f });
	Player->SetActorLocation(FVector{ 640.0f, -360.0f, 200.0f });
	ColMap->SetActorLocation(FVector{ 3100.0f, -405.0f, 500.0f });

	Camera->SetIsCameraMove(true);
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