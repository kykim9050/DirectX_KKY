#include "PreCompile.h"
#include <EngineCore/Camera.h>
#include <EngineCore/EngineEditorGUI.h>

#include "TitleMode.h"
#include "TitleLogo.h"
#include "TitleAnimation.h"
#include "ContentsDebugWindow.h"

ATitleMode::ATitleMode() 
{

}

ATitleMode::~ATitleMode()
{
}

void ATitleMode::BeginPlay()
{
	Super::BeginPlay();

	CreateDebugWindow();

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

	BGMPlayer.Off();

	DeleteObject();
	InputOff();
}

void ATitleMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	BGMPlayer = UEngineSound::SoundPlay("Title_bgm.wav");
	BGMPlayer.Loop();

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
		ModeState.SetStartFunction("Idle", [this]()
			{
				Iris->SetActive(false);
			});
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
		ModeState.SetUpdateFunction("WorldLevelChange", [](float){});
	}

	ModeState.ChangeState("Idle");
}

void ATitleMode::Idle(float _DeltaTime)
{
	if (true == IsAnykeyDown()
		&& false == IsDown(VK_LBUTTON)
		&& false == IsDown(VK_RBUTTON)
		&& false == IsDown(VK_MBUTTON))
	{
		ModeState.ChangeState("WorldLevelChange");
		return;
	}
}

void ATitleMode::CreateDebugWindow()
{
	DebugWindow = UEngineEditorGUI::CreateEditorWindow<UContentsDebugWindow>("ContentsDebugWindow");
	DebugWindow->On();
}
