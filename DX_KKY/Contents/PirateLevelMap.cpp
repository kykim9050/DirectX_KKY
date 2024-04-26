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
	Wave1->SetAutoSize(1.0f, true);
	Wave2->SetAutoSize(1.0f, true);
	Wave3->SetAutoSize(1.0f, true);
	Wave4->SetAutoSize(1.0f, true);

	Wave1->SetOrder(ERenderingOrder::Wave1);
	Wave2->SetOrder(ERenderingOrder::Wave2);
	Wave3->SetOrder(ERenderingOrder::Wave3);
	Wave4->SetOrder(ERenderingOrder::Wave4);

	Wave1->SetPivot(EPivot::BOT);
	Wave2->SetPivot(EPivot::BOT);
	Wave3->SetPivot(EPivot::BOT);
	Wave4->SetPivot(EPivot::BOT);


	Wave1->SetPosition(float4(0.0f, -360.0f, 0.0f));
	Wave2->SetPosition(float4(0.0f, -360.0f, 0.0f));
	Wave3->SetPosition(float4(0.0f, -260.0f, 0.0f));
	Wave4->SetPosition(float4(0.0f, -160.0f, 0.0f));
}

void APirateLevelMap::AnimationInit()
{
	Wave1->CreateAnimation("Wave1","Water_A", 0.034f, true);
	Wave2->CreateAnimation("Wave2", "Water_B", 0.034f, true);
	Wave3->CreateAnimation("Wave3", "Water_C", 0.034f, true);
	Wave4->CreateAnimation("Wave4", "Water_D", 0.034f, true);

	Wave1->ChangeAnimation("Wave1");
	Wave2->ChangeAnimation("Wave2");
	Wave3->ChangeAnimation("Wave3");
	Wave4->ChangeAnimation("Wave4");
}