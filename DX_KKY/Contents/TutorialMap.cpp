#include "PreCompile.h"
#include "TutorialMap.h"

ATutorialMap::ATutorialMap()
{
}

ATutorialMap::~ATutorialMap()
{
}

void ATutorialMap::BeginPlay()
{
	Super::BeginPlay();

	SetMapFile("tutorial_object.png");
	SetMapScale(FVector{6200.0f, 810.0f, 0.0f});

}

void ATutorialMap::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}