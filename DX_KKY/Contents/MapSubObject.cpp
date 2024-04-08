#include "PreCompile.h"
#include "MapSubObject.h"

AMapSubObject::AMapSubObject()
{
}

AMapSubObject::~AMapSubObject()
{
}

void AMapSubObject::BeginPlay()
{
	Super::BeginPlay();

	SetMapFile("tutorial_room_back_layer_0001.png");
	SetMapScale(FVector{ 1280.0f, 720.0f, 0.0f });
}

void AMapSubObject::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
