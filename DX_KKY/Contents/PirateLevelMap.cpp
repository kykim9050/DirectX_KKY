#include "PreCompile.h"
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>

#include "PirateLevelMap.h"

APirateLevelMap::APirateLevelMap()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("MapRoot");
	SetRoot(Root);

	Wave1 = CreateDefaultSubObject<USpriteRenderer>("Wave1");
	Wave1->SetupAttachment(Root);
	
	Wave2 = CreateDefaultSubObject<USpriteRenderer>("Wave2");
	Wave2->SetupAttachment(Root);

	Wave3 = CreateDefaultSubObject<USpriteRenderer>("Wave3");
	Wave3->SetupAttachment(Root);

	Wave4 = CreateDefaultSubObject<USpriteRenderer>("Wave4");
	Wave4->SetupAttachment(Root);

	Dock = CreateDefaultSubObject<USpriteRenderer>("Dock");
	Dock->SetupAttachment(Root);

	DockLog = CreateDefaultSubObject<USpriteRenderer>("DockLog");
	DockLog->SetupAttachment(Root);

	DefaultSky = CreateDefaultSubObject<USpriteRenderer>("DefaultSky");
	DefaultSky->SetupAttachment(Root);

}

APirateLevelMap::~APirateLevelMap()
{
}

void APirateLevelMap::BeginPlay()
{
	Super::BeginPlay();

	RendererInit();
	AnimationInit();
}

void APirateLevelMap::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void APirateLevelMap::RendererInit()
{
	// Wave
	Wave1->SetAutoSize(1.3f, true);
	Wave2->SetAutoSize(1.3f, true);
	Wave3->SetAutoSize(1.3f, true);
	Wave4->SetAutoSize(1.3f, true);

	Wave1->SetOrder(ERenderingOrder::Wave1);
	Wave2->SetOrder(ERenderingOrder::Wave2);
	Wave3->SetOrder(ERenderingOrder::Wave3);
	Wave4->SetOrder(ERenderingOrder::Wave4);

	Wave1->SetPivot(EPivot::BOT);
	Wave2->SetPivot(EPivot::BOT);
	Wave3->SetPivot(EPivot::BOT);
	Wave4->SetPivot(EPivot::BOT);

	Wave1->SetPosition(GRendererPos::Wave1_Pos);
	Wave2->SetPosition(GRendererPos::Wave2_Pos);
	Wave3->SetPosition(GRendererPos::Wave3_Pos);
	Wave4->SetPosition(GRendererPos::Wave4_Pos);

	//Dock
	Dock->SetAutoSize(1.0f, true);
	Dock->SetOrder(ERenderingOrder::Object1);
	Dock->SetPivot(EPivot::LEFTBOTTOM);
	Dock->SetPosition(GRendererPos::Dock_Pos);

	DockLog->SetAutoSize(1.0f, true);
	DockLog->SetOrder(ERenderingOrder::DockLog);
	DockLog->SetPivot(EPivot::LEFTBOTTOM);
	DockLog->SetPosition(GRendererPos::DockLog_Pos);

	//Sky
	DefaultSky->SetAutoSize(1.3f, true);
	DefaultSky->SetOrder(ERenderingOrder::BackLayer3);
	DefaultSky->SetPosition(GRendererPos::PirateLevel_DefaultSky_Pos);
}

void APirateLevelMap::AnimationInit()
{
	Wave1->CreateAnimation("Wave1","Water_A", 0.04f, true);
	Wave2->CreateAnimation("Wave2", "Water_B", 0.04f, true);
	Wave3->CreateAnimation("Wave3", "Water_C", 0.04f, true);
	Wave4->CreateAnimation("Wave4", "Water_D", 0.04f, true);

	Wave1->ChangeAnimation("Wave1");
	Wave2->ChangeAnimation("Wave2");
	Wave3->ChangeAnimation("Wave3");
	Wave4->ChangeAnimation("Wave4");

	Dock->SetSprite("pirateDockA.png");
	DockLog->SetSprite("pirateDockB.png");

	DefaultSky->SetSprite("pirate_clouds_D.png");
}