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

	SoundResourceLoad();
	ImgResourceLoad();
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

void ALoadingMode::ImgResourceLoad()
{
	UEngineDirectory Dir;

	// Bullet
	Dir.MoveToSearchChild("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Bullet");
	std::vector<UEngineDirectory> Directorys1 = Dir.GetAllDirectory(true);
	LoadingCount += static_cast<int>(Directorys1.size());

	// Cuphead
	Dir.MoveToSearchChild("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Cuphead");
	std::vector<UEngineDirectory> Directorys2 = Dir.GetAllDirectory(true);
	LoadingCount += static_cast<int>(Directorys2.size());

	// Effect
	Dir.MoveToSearchChild("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Effect");
	std::vector<UEngineDirectory> Directorys3 = Dir.GetAllDirectory(true);
	LoadingCount += static_cast<int>(Directorys3.size());

	// Ending
	Dir.MoveToSearchChild("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Ending");
	std::vector<UEngineDirectory> Directorys4 = Dir.GetAllDirectory(true);
	LoadingCount += static_cast<int>(Directorys4.size());

	// Flower
	Dir.MoveToSearchChild("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Flower");
	std::vector<UEngineDirectory> Directorys5 = Dir.GetAllDirectory(true);
	LoadingCount += static_cast<int>(Directorys5.size());


	// Pirate
	Dir.MoveToSearchChild("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Pirate");
	std::vector<UEngineDirectory> Directorys6 = Dir.GetAllDirectory(true);
	LoadingCount += static_cast<int>(Directorys6.size());

	// Title
	Dir.MoveToSearchChild("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Title");
	std::vector<UEngineDirectory> Directorys7 = Dir.GetAllDirectory(true);
	LoadingCount += static_cast<int>(Directorys7.size());

	// Tutorial
	Dir.MoveToSearchChild("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Tutorial");
	std::vector<UEngineDirectory> Directorys8 = Dir.GetAllDirectory(true);
	LoadingCount += static_cast<int>(Directorys8.size());

	// World
	Dir.MoveToSearchChild("ContentsResources");
	Dir.Move("Image");
	Dir.Move("World");
	std::vector<UEngineDirectory> Directorys9 = Dir.GetAllDirectory(true);
	LoadingCount += static_cast<int>(Directorys9.size());

	// SingleFileRes
	Dir.MoveToSearchChild("ContentsResources");
	Dir.Move("Image");
	Dir.Move("SingleFileRes");
	std::vector<UEngineFile> Files = Dir.GetAllFile({ ".png" }, true);
	LoadingCount += static_cast<int>(Files.size());


	// Bullet
	for (size_t i = 0; i < Directorys1.size(); i++)
	{
		std::string Name = Directorys1[i].GetFolderName();

		GEngine->JobWorker.Work([=]()
			{
				UEngineSprite::ThreadSafeLoadFolder(Directorys1[i].GetFullPath());
				LoadingCount--;
			});
	}

	// Cuphead
	for (size_t i = 0; i < Directorys2.size(); i++)
	{
		std::string Name = Directorys2[i].GetFolderName();

		GEngine->JobWorker.Work([=]()
			{
				UEngineSprite::ThreadSafeLoadFolder(Directorys2[i].GetFullPath());
				LoadingCount--;
			});
	}

	// Effect
	for (size_t i = 0; i < Directorys3.size(); i++)
	{
		std::string Name = Directorys3[i].GetFolderName();

		GEngine->JobWorker.Work([=]()
			{
				UEngineSprite::ThreadSafeLoadFolder(Directorys3[i].GetFullPath());
				LoadingCount--;
			});
	}

	// Ending
	for (size_t i = 0; i < Directorys4.size(); i++)
	{
		std::string Name = Directorys4[i].GetFolderName();

		GEngine->JobWorker.Work([=]()
			{
				UEngineSprite::ThreadSafeLoadFolder(Directorys4[i].GetFullPath());
				LoadingCount--;
			});
	}

	// Flower
	for (size_t i = 0; i < Directorys5.size(); i++)
	{
		std::string Name = Directorys5[i].GetFolderName();

		GEngine->JobWorker.Work([=]()
			{
				UEngineSprite::ThreadSafeLoadFolder(Directorys5[i].GetFullPath());
				LoadingCount--;
			});
	}


	// Pirate
	for (size_t i = 0; i < Directorys6.size(); i++)
	{
		std::string Name = Directorys6[i].GetFolderName();

		GEngine->JobWorker.Work([=]()
			{
				UEngineSprite::ThreadSafeLoadFolder(Directorys6[i].GetFullPath());
				LoadingCount--;
			});
	}


	// Title
	for (size_t i = 0; i < Directorys7.size(); i++)
	{
		std::string Name = Directorys7[i].GetFolderName();

		GEngine->JobWorker.Work([=]()
			{
				UEngineSprite::ThreadSafeLoadFolder(Directorys7[i].GetFullPath());
				LoadingCount--;
			});
	}


	// Tutorial
	for (size_t i = 0; i < Directorys8.size(); i++)
	{
		std::string Name = Directorys8[i].GetFolderName();

		GEngine->JobWorker.Work([=]()
			{
				UEngineSprite::ThreadSafeLoadFolder(Directorys8[i].GetFullPath());
				LoadingCount--;
			});
	}


	// World
	for (size_t i = 0; i < Directorys9.size(); i++)
	{
		std::string Name = Directorys9[i].GetFolderName();

		GEngine->JobWorker.Work([=]()
			{
				UEngineSprite::ThreadSafeLoadFolder(Directorys9[i].GetFullPath());
				LoadingCount--;
			});
	}

	// SingleFileRes
	for (UEngineFile& File : Files)
	{
		GEngine->JobWorker.Work([=]()
			{
				UEngineSprite::ThreadSafeLoad(File.GetFullPath());
				LoadingCount--;
			});
	}
}

void ALoadingMode::SoundResourceLoad()
{
	UEngineDirectory Dir;
	Dir.MoveToSearchChild("ContentsResources");
	Dir.Move("Sound");
	std::vector<UEngineFile> Files = Dir.GetAllFile({ ".mp3", ".wav" }, true);

	for (UEngineFile& File : Files)
	{
		UEngineSound::Load(File.GetFullPath());
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