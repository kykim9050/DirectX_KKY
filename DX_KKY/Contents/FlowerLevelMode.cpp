#include "PreCompile.h"
#include <EngineCore/Camera.h>

#include "FlowerLevelMode.h"


#include "OldFilmEffect.h"
#include "Player.h"
#include "MapBase.h"
#include "CagneyCarnation.h"
#include "FlowerPlatform.h"
#include "PlatformShadow.h"
#include "Message.h"

AFlowerLevelMode::AFlowerLevelMode()
{
}

AFlowerLevelMode::~AFlowerLevelMode()
{
}

void AFlowerLevelMode::BeginPlay()
{
	Super::BeginPlay();

	WidgetInit();
	CreateObject();
	GetWorld()->GetLastTarget()->AddEffect<UBlurEffect>();
}

void AFlowerLevelMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AFlowerLevelMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);

	UContentsValue::ColMapTexture = nullptr;

	ObjectDelete();
}

void AFlowerLevelMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	ObjectInit();

	OldFilm->ChangeAnimation("OldFilmAni");
	Iris->ChangeAnimation("IrisAni");

	DelayCallBack(0.5f, [this]()
		{
			ScreenMsg = GetWorld()->SpawnActor<AMessage>("ScreenMsg", EActorType::ScreenMsg).get();
			ScreenMsg->SetStageStartMsg();
		});
	
}

void AFlowerLevelMode::WidgetInit()
{
	OldFilm = CreateWidget<UImage>(GetWorld(), "OldFilm");
	OldFilm->AddToViewPort(ERenderingOrder::OldFilmEffect);
	OldFilm->CreateAnimation("OldFilmAni", "OldFilmEffect", 0.05f);
	OldFilm->SetPosition(float4(0.0f, 0.0f, 0.0f));
	OldFilm->SetScale(GEngine->EngineWindow.GetWindowScale());

	Iris = CreateWidget<UImage>(GetWorld(), "Iris");
	Iris->AddToViewPort(ERenderingOrder::Iris);
	Iris->CreateAnimation("IrisAni", "Iris", 0.034f, false);
	Iris->SetPosition(float4(0.0f, 0.0f, 0.0f));
	Iris->SetScale(GEngine->EngineWindow.GetWindowScale());
}

void AFlowerLevelMode::CreateObject()
{
	Camera = GetWorld()->GetMainCamera();

	MapFrontObject = GetWorld()->SpawnActor<AMapBase>("MapFrontObject", EActorType::Map);
	Map = GetWorld()->SpawnActor<AMapBase>("Map", EActorType::Map);
	BackGroundObject = GetWorld()->SpawnActor<AMapBase>("BackGroundObject", EActorType::Map);
	ColMap = GetWorld()->SpawnActor<AMapBase>("ColMap", EActorType::Map);

	for (int i = 0; i < ShadowNum; i++)
	{
		std::shared_ptr<APlatformShadow> Shadow = GetWorld()->SpawnActor<APlatformShadow>("Shadow", EActorType::Object);
		Shadow->SetActorLocation(FlowerBossStageValue::PlatformShadowPos[i]);

		Shadows.push_back(Shadow);
	}
}

void AFlowerLevelMode::ObjectInit()
{
	Player = GetWorld()->SpawnActor<APlayer>("Player", EActorType::Player);
	BossMonster = GetWorld()->SpawnActor<ACagneyCarnation>("BossMonster", EActorType::BossMonster);

	Camera->SetActorLocation(UContentsValue::ContentsCameraInitPos);
	Player->SetActorLocation(FVector{ 640.0f, -400.0f, 100.0f });
	BossMonster->SetActorLocation(FVector{ 1380.0f, -680.0f, 100.0f });

	MapFrontObject->SetMapFile("Flower_Background_Front.png");
	MapFrontObject->SetAutoScale();
	MapFrontObject->SetActorLocation(FVector(630.0f, -575.0f, 50.0f));
	MapFrontObject->SetOrdering(ERenderingOrder::FrontLayer);

	Map->SetMapFile("Flower_Background.png");
	Map->SetAutoScale();
	Map->SetActorLocation(FVector(689.0f, -404.0f, 200.0f));
	Map->SetOrdering(ERenderingOrder::BackLayer1);

	BackGroundObject->SetMapFile("Flower_Background_Cloud02.png");
	BackGroundObject->SetAutoScale();
	BackGroundObject->SetActorLocation(FVector(700.0f, -233.0f, 300.0f));
	BackGroundObject->SetOrdering(ERenderingOrder::BackLayer2);

	ColMap->SetMapFile("Flower_Background_PixelCheck.png");
	ColMap->SetAutoScale();
	ColMap->SetOrdering(ERenderingOrder::CollisionLayer);
	ColMap->SetActorLocation(FVector(640.0f, -360.0f, 400.0f));
	ColMap->SetOrdering(ERenderingOrder::CollisionLayer);
	UContentsValue::ColMapTexture = UEngineTexture::FindRes(ColMap->GetName());

	Platform1 = GetWorld()->SpawnActor<AFlowerPlatform>("Platform1", EActorType::Object);
	Platform2 = GetWorld()->SpawnActor<AFlowerPlatform>("Platform2", EActorType::Object);
	Platform3 = GetWorld()->SpawnActor<AFlowerPlatform>("Platform3", EActorType::Object);

	Platform1->CreatePlatformAnimation(FAniInfo(FlowerBossAniName::FlowerPlatform, "FlowerPlatform0", 0.067f));
	Platform1->ChangePlatformAnimation(FlowerBossAniName::FlowerPlatform);
	Platform1->SetActorLocation(FlowerBossStageValue::PlatformPos[0]);

	Platform2->CreatePlatformAnimation(FAniInfo(FlowerBossAniName::FlowerPlatform, "FlowerPlatform1", 0.067f));
	Platform2->ChangePlatformAnimation(FlowerBossAniName::FlowerPlatform);
	Platform2->SetActorLocation(FlowerBossStageValue::PlatformPos[1]);

	Platform3->CreatePlatformAnimation(FAniInfo(FlowerBossAniName::FlowerPlatform, "FlowerPlatform2", 0.067f));
	Platform3->ChangePlatformAnimation(FlowerBossAniName::FlowerPlatform);
	Platform3->SetActorLocation(FlowerBossStageValue::PlatformPos[2]);
}

void AFlowerLevelMode::ObjectDelete()
{
	Player->Destroy();
	Player = nullptr;

	BossMonster->Destroy();
	BossMonster = nullptr;

	Platform1->Destroy();
	Platform2->Destroy();
	Platform3->Destroy();
	Platform1 = nullptr;
	Platform2 = nullptr;
	Platform3 = nullptr;
}

