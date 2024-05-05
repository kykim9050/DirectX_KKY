#include "PreCompile.h"
#include <EngineCore/DefaultSceneComponent.h>

#include "CallSeaDogs.h"
#include "FXBase.h"

ACallSeaDogs::ACallSeaDogs()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");
	SetRoot(Root);
}

ACallSeaDogs::~ACallSeaDogs()
{
}

void ACallSeaDogs::BeginPlay()
{
	Super::BeginPlay();

	CreatePeriscope();
	CreateSeaDogs();
}

void ACallSeaDogs::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void ACallSeaDogs::CreatePeriscope()
{
	std::shared_ptr<AFXBase> Periscope = GetWorld()->SpawnActor<AFXBase>("Periscope", EActorType::FX);
	Periscope->FXInit(ERenderingOrder::SubMonster1FX, FAniInfo(PirateBossAniName::SeaDog_Periscope, "SeaDog_Periscope.png", 0.0416f));
	Periscope->SetImgPivot(EPivot::RIGHTBOTTOM);
	Periscope->SetActorLocation(GActorPosValue::Periscope_Init_Pos);
}

void ACallSeaDogs::CreateSeaDogs()
{

}