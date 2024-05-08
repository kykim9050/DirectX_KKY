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
#include "TimeScaleControlUnit.h"

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

	ModeState.Update(_DeltaTime);
}

void AFlowerLevelMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);

	ObjectDelete();

	BGMPlayer.Off();
}

void AFlowerLevelMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);


	ObjectInit();
	StateInit();

	OldFilm->ChangeAnimation(GAniName::OldFilmAni);
	Iris->ChangeAnimation(GAniName::IrisAni);
	
	BGMPlayer = UEngineSound::SoundPlay("FlowerLevel_bgm.wav");
	BGMPlayer.SetVolume(0.5f);
	BGMPlayer.Loop();
}

void AFlowerLevelMode::WidgetInit()
{
	OldFilm = CreateWidget<UImage>(GetWorld(), "OldFilm");
	OldFilm->AddToViewPort(ERenderingOrder::OldFilmEffect);
	OldFilm->CreateAnimation(GAniName::OldFilmAni, GSpriteName::OldFilm, 0.05f);
	OldFilm->SetPosition(float4(0.0f, 0.0f, 0.0f));
	OldFilm->SetScale(GEngine->EngineWindow.GetWindowScale());

	Iris = CreateWidget<UImage>(GetWorld(), "Iris");
	Iris->AddToViewPort(ERenderingOrder::Iris);
	Iris->CreateAnimation(GAniName::IrisAni, GSpriteName::Iris, 0.034f, false);
	Iris->CreateAnimation(GAniName::IrisRevAni, GSpriteName::Iris, 0.034f, false, 16, 0);
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
	ScreenMsg = GetWorld()->SpawnActor<AMessage>("ScreenMsg", EActorType::ScreenMsg);

	TimeControlUnit = GetWorld()->SpawnActor<UTimeScaleControlUnit>("TimeControlUnit", EActorType::TimeScaleController);
	
	Player = GetWorld()->SpawnActor<APlayer>("Player", EActorType::Player);

	Camera->SetActorLocation(UContentsValue::ContentsCameraInitPos);
	Player->SetActorLocation(FVector{ 640.0f, -400.0f, 100.0f });

	MapFrontObject->SetMapFile("Flower_Background_Front.png");
	MapFrontObject->SetAutoScale();
	MapFrontObject->SetActorLocation(FVector(630.0f, -575.0f, 50.0f));
	MapFrontObject->SetOrdering(ERenderingOrder::FrontLayer2);

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
	UContentsValue::ColMapTexture = nullptr;

	if (nullptr != Player)
	{
		Player->Destroy();
		Player = nullptr;
	}

	if (nullptr != BossMonster)
	{
		BossMonster->Destroy();
		BossMonster = nullptr;
	}

	if (nullptr != Platform1)
	{
		Platform1->Destroy();
		Platform1 = nullptr;
	}

	if (nullptr != Platform2)
	{
		Platform2->Destroy();
		Platform2 = nullptr;
	}

	if (nullptr != Platform3)
	{
		Platform3->Destroy();
		Platform3 = nullptr;
	}

	if (nullptr != TimeControlUnit)
	{
		TimeControlUnit->Destroy();
		TimeControlUnit = nullptr;
	}

	if (nullptr != ScreenMsg)
	{
		ScreenMsg->Destroy();
		ScreenMsg = nullptr;
	}
}

void AFlowerLevelMode::StateInit()
{
	{
		ModeState.CreateState("Phase1");
		ModeState.CreateState("GameEnd");
	}

	{
		ModeState.SetStartFunction("Phase1", [this]()
			{
				// 페이즈1 보스 생성
				DelayCallBack(0.8f, [this]()
					{
						ScreenMsg->SetStageStartMsg();
					});

				BossMonster = GetWorld()->SpawnActor<ACagneyCarnation>("BossMonster", EActorType::BossMonster);
				BossMonster->SetActorLocation(FVector{ 1380.0f, -680.0f, 100.0f });
			});
		ModeState.SetStartFunction("GameEnd", [this]()
			{
				BGMPlayer.Off();

				ScreenMsg->SetStageEndMsg();

				Iris->SetFrameCallback(GAniName::IrisRevAni, 17, [this]()
					{
						GEngine->ChangeLevel(GLevelName::WorldLevel);
					});

				// 레벨 전환 기능
				DelayCallBack(3.5f, [this]()
					{
						Iris->ChangeAnimation(GAniName::IrisRevAni);
					});
			});
	}

	{
		ModeState.SetUpdateFunction("Phase1", std::bind(&AFlowerLevelMode::Phase1, this, std::placeholders::_1));
		ModeState.SetUpdateFunction("GameEnd", [](float) {});
	}

	ModeState.ChangeState("Phase1");
}

void AFlowerLevelMode::Phase1(float _DeltaTime)
{
	if (true == BossMonster->GetIsPhaseEnd())
	{
		ModeState.ChangeState("GameEnd");
		return;
	}
}