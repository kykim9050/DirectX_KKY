#include "PreCompile.h"
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/Collision.h>

#include "FlowerLevelGate.h"

AFlowerLevelGate::AFlowerLevelGate()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");
	SetRoot(Root);

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);

	Collider = CreateDefaultSubObject<UCollision>("Collider");
	Collider->SetupAttachment(Root);
}

AFlowerLevelGate::~AFlowerLevelGate()
{
}

void AFlowerLevelGate::BeginPlay()
{
	Super::BeginPlay();
}

void AFlowerLevelGate::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
