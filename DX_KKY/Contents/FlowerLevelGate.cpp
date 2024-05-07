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

	RendererInit();
	ColliderInit();
}

void AFlowerLevelGate::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AFlowerLevelGate::RendererInit()
{
	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetOrder(ERenderingOrder::Object1);

	Renderer->CreateAnimation(GAniName::FlowerLevel_GateAni, "FloralFury_Garden.png", 0.1f);
	Renderer->ChangeAnimation(GAniName::FlowerLevel_GateAni);
}

void AFlowerLevelGate::ColliderInit()
{
	Collider->SetScale(GColliderScale::FlowerGate_ColScale);
	Collider->SetCollisionGroup(ECollisionGroup::Gate);
	Collider->SetCollisionType(ECollisionType::Rect);
}