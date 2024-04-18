#include "PreCompile.h"
#include <EngineCore/DefaultSceneComponent.h>

#include "BossUnit.h"

ABossUnit::ABossUnit()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("BulletRoot");
	SetRoot(Root);

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);

	Collision = CreateDefaultSubObject<UCollision>("Collision");
	Collision->SetupAttachment(Root);
}

ABossUnit::~ABossUnit()
{
}

void ABossUnit::BeginPlay()
{
	Super::BeginPlay();
}

void ABossUnit::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}