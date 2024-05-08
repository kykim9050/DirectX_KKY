#include "PreCompile.h"
#include <EngineCore/Camera.h>

#include "TitleMode.h"
#include "TitleLogo.h"
#include "TitleAnimation.h"
#include "ContentsEnumClass.h"

ATitleMode::ATitleMode() 
{

}

ATitleMode::~ATitleMode()
{
}

void ATitleMode::BeginPlay()
{
	Super::BeginPlay();

	Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(0.0f, 0.0f, UContentsValue::CameraInitZValue));
	WidgetInit();
	GetWorld()->GetLastTarget()->AddEffect<UBlurEffect>();
}

void ATitleMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	ModeState.Update(_DeltaTime);
}

void ATitleMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);

	DeleteObject();
	InputOff();
}

void ATitleMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	WidgetStart();
	CreateObject();
	StateInit();
	InputOn();
}

void ATitleMode::WidgetInit()
{
	OldFilm = CreateWidget<UImage>(GetWorld(), "OldFilm");
	OldFilm->AddToViewPort(ERenderingOrder::OldFilmEffect);
	OldFilm->SetPosition(float4(0.0f, 0.0f, 0.0f));
	OldFilm->SetScale(GEngine->EngineWindow.GetWindowScale());
	OldFilm->CreateAnimation(GAniName::OldFilmAni, GSpriteName::OldFilm, 0.05f);

	Iris = CreateWidget<UImage>(GetWorld(), "Iris");
	Iris->AddToViewPort(ERenderingOrder::Iris);
	Iris->SetPosition(float4(0.0f, 0.0f, 0.0f));
	Iris->SetScale(GEngine->EngineWindow.GetWindowScale());
	Iris->CreateAnimation(GAniName::IrisRevAni, GSpriteName::Iris, 0.034f, false, 16, 0);
	Iris->SetActive(false);
}

void ATitleMode::WidgetStart()
{
	OldFilm->ChangeAnimation(GAniName::OldFilmAni);
}

void ATitleMode::CreateObject()
{
	TitleAni = GetWorld()->SpawnActor<ATitleAnimation>("TitleAnimation", static_cast<int>(EActorType::BackGroundAnimation));
	TitleLogo = GetWorld()->SpawnActor<ATitleLogo>("TitleLogo", static_cast<int>(EActorType::BackGroundSubStaticObject));
}

void ATitleMode::DeleteObject()
{
	if (nullptr != TitleAni)
	{
		TitleAni->Destroy();
		TitleAni = nullptr;
	}

	if (nullptr != TitleLogo)
	{
		TitleLogo->Destroy();
		TitleLogo = nullptr;
	}
}

void ATitleMode::StateInit()
{
	{
		ModeState.CreateState("Idle");
		ModeState.CreateState("WorldLevelChange");
	}

	{
		ModeState.SetStartFunction("WorldLevelChange", [this]()
			{
				Iris->SetFrameCallback(GAniName::IrisRevAni, 17, [this]()
					{
						GEngine->ChangeLevel(GLevelName::WorldLevel);
					});

				Iris->SetActive(true);
				Iris->ChangeAnimation(GAniName::IrisRevAni);
			});
	}

	{
		ModeState.SetUpdateFunction("Idle", std::bind(&ATitleMode::Idle, this, std::placeholders::_1));
		ModeState.SetUpdateFunction("WorldLevelChange", [](float) {});
	}

	ModeState.ChangeState("Idle");
}

void ATitleMode::Idle(float _DeltaTime)
{
	if (true == IsAnykeyDown())
	{
		ModeState.ChangeState("WorldLevelChange");
		return;
	}
}