#include "PreCompile.h"
#include <EngineCore/SpriteRenderer.h>

#include "BackGroundCloud.h"

ABackGroundCloud::ABackGroundCloud()
{
	CloudRenderer = CreateDefaultSubObject<USpriteRenderer>("Cloud");
	SetRoot(CloudRenderer);
}

ABackGroundCloud::~ABackGroundCloud()
{
}


void ABackGroundCloud::BeginPlay()
{
	Super::BeginPlay();

	RendererInit();
}

void ABackGroundCloud::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	CloudMoving(_DeltaTime);
}

void ABackGroundCloud::CloudMoving(float _DeltaTime)
{
	AccTime += _DeltaTime;

	CloudRenderer->SetVertexUVPlus(float4(AccTime * 0.13f, 0.0f, 0.0f));
}

void ABackGroundCloud::RendererInit()
{
	CloudRenderer->SetAutoSize(1.0f, true);
	CloudRenderer->SetOrder(ERenderingOrder::BackLayer2);
	CloudRenderer->SetPivot(EPivot::BOT);
	CloudRenderer->SetPosition(GRendererPos::PirateLevel_Cloud1_Pos);
	CloudRenderer->SetSprite("Flower_Background_Cloud01.png");
}