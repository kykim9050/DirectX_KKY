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
}

void ATutorialMap::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}