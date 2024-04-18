#include "PreCompile.h"
#include <EngineCore/DefaultSceneComponent.h>

#include "BulletUnit.h"

ABulletUnit::ABulletUnit()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("BulletRoot");
	SetRoot(Root);

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);
	
	Collision = CreateDefaultSubObject<UCollision>("Collision");
	Collision->SetupAttachment(Root);
}

ABulletUnit::~ABulletUnit()
{
}

void ABulletUnit::BeginPlay()
{
	Super::BeginPlay();
}

void ABulletUnit::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}