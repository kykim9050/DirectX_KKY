#include "PreCompile.h"

#include "LoadingMode.h"
#include "LoadActor.h"
#include "TitleMode.h"
#include "EndingMode.h"
#include "WorldGameMode.h"
#include "FlowerLevelMode.h"
#include "PirateLevelMode.h"

ALoadingMode::ALoadingMode()
{

}

ALoadingMode::~ALoadingMode()
{
}

void ALoadingMode::BeginPlay()
{
	Super::BeginPlay();

	FirstResourceLoad();
	CreateActor();
	GetWorld()->GetLastTarget()->AddEffect<UBlurEffect>();
}

void ALoadingMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (0 == LoadingCount)
	{
		LoadingCount = -1;
		CuttingImgSet();
		CreateAllLevel();
		GEngine->ChangeLevel(GLevelName::TitleLevel);
		return;
	}
}

void ALoadingMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);

	ReleaseActor();
}

void ALoadingMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	ResourceLoad();
}

void ALoadingMode::CreateActor()
{
	OldFilm = CreateWidget<UImage>(GetWorld(), "OldFilm");
	OldFilm->AddToViewPort(ERenderingOrder::OldFilmEffect);
	OldFilm->CreateAnimation(GAniName::OldFilmAni, GSpriteName::OldFilm, 0.05f);
	OldFilm->SetScale(GEngine->EngineWindow.GetWindowScale());
	OldFilm->ChangeAnimation(GAniName::OldFilmAni);

	LoadActor = GetWorld()->SpawnActor<ALoadActor>("LoadActor");

	Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(UContentsValue::ContentsCameraInitPos);
}

void ALoadingMode::ReleaseActor()
{
	if (nullptr != Camera)
	{
		Camera->Destroy();
		Camera = nullptr;
	}

	if (nullptr != LoadActor)
	{
		LoadActor->Destroy();
		LoadActor = nullptr;
	}
}

void ALoadingMode::FirstResourceLoad()
{
	UEngineDirectory Dir;
	Dir.MoveToSearchChild("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Screen");
	std::vector<UEngineFile> Files = Dir.GetAllFile({ ".png" }, true);
	std::vector<UEngineDirectory> Directorys = Dir.GetAllDirectory(true);

	for (UEngineFile& File : Files)
	{
		UEngineSprite::Load(File.GetFullPath());
	}

	for (size_t i = 0; i < Directorys.size(); i++)
	{
		UEngineSprite::LoadFolder(Directorys[i].GetFullPath());
	}
}

void ALoadingMode::ResourceLoad()
{
	// Bullet
	// Cuphead
	// Effect
	// Ending_Animation
	// Flower
	// Pirate
	// Title
	// Tutorial
	// World

	UEngineDirectory Dir;
	Dir.MoveToSearchChild("ContentsResources");
	Dir.Move("Image");
	Dir.Move("OtherRes");
	std::vector<UEngineFile> Files = Dir.GetAllFile({ ".png" }, true);
	std::vector<UEngineDirectory> Directorys = Dir.GetAllDirectory(true);

	LoadingCount = static_cast<int>(Files.size()) + static_cast<int>(Directorys.size());


	for (UEngineFile& File : Files)
	{
		GEngine->JobWorker.Work([=]()
			{
				UEngineSprite::ThreadSafeLoad(File.GetFullPath());
				LoadingCount--;
			});
	}

	for (size_t i = 0; i < Directorys.size(); i++)
	{
		std::string Name = Directorys[i].GetFolderName();

		GEngine->JobWorker.Work([=]()
			{
				UEngineSprite::ThreadSafeLoadFolder(Directorys[i].GetFullPath());
				LoadingCount--;
			});
	}
}

void ALoadingMode::CreateAllLevel()
{
	GEngine->CreateLevel<ATitleMode>(GLevelName::TitleLevel);
	GEngine->CreateLevel<AEndingMode>(GLevelName::EndingLevel);
	GEngine->CreateLevel<AWorldGameMode>(GLevelName::WorldLevel);
	GEngine->CreateLevel<AFlowerLevelMode>(GLevelName::FlowerLevel);
	GEngine->CreateLevel<APirateLevelMode>(GLevelName::PirateLevel);
}

void ALoadingMode::CuttingImgSet()
{
	UEngineSprite::CreateCutting("Barrel_Normal_Idle.png", 6, 2);
	UEngineSprite::CreateCutting("Pirate_Barrel_AttWait_Idle.png", 6, 2);
	UEngineSprite::CreateCutting("Pirate_Barrel_Drop.png", 4, 1);
	UEngineSprite::CreateCutting("Pirate_Barrel_Smash.png", 5, 1);
	UEngineSprite::CreateCutting("Pirate_Barrel_BackUp.png", 6, 1);
	UEngineSprite::CreateCutting("Barrel_Smash_Dust.png", 8, 3);
	UEngineSprite::CreateCutting("Barrel_Smash_FX.png", 6, 2);
	UEngineSprite::CreateCutting("Shark_Fin.png", 3, 1);
	UEngineSprite::CreateCutting("Shark_Appear.png", 6, 1);
	UEngineSprite::CreateCutting("Shark_Chomp1.png", 5, 2);
	UEngineSprite::CreateCutting("Shark_Chomp2.png", 3, 1);
	UEngineSprite::CreateCutting("Shark_Leave.png", 8, 1);
	UEngineSprite::CreateCutting("Shark_Appear_Effect.png", 11, 2);

	UEngineSprite::CreateCutting("SeaDog_Appear.png", 11, 2);
	UEngineSprite::CreateCutting("SeaDog_Appear_Effect.png", 6, 2);
	UEngineSprite::CreateCutting("SeaDog_Death.png", 8, 1);
	UEngineSprite::CreateCutting("SeaDog_Death_Effect.png", 5, 2);
	UEngineSprite::CreateCutting("SeaDog_Move.png", 6, 2);
	UEngineSprite::CreateCutting("SeaDog_Periscope.png", 10, 5);

	UEngineSprite::CreateCutting("FloralFury_Garden.png", 3, 1);
	UEngineSprite::CreateCutting("ShootinNLootin_Ripples.png", 3, 1);
	UEngineSprite::CreateCutting("ShootinNLootin_Ship.png", 3, 1);
}