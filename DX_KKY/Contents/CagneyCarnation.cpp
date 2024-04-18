#include "PreCompile.h"

#include "CagneyCarnation.h"
#include <EngineCore/SpriteRenderer.h>

ACagneyCarnation::ACagneyCarnation()
{
}

ACagneyCarnation::~ACagneyCarnation()
{
}

void ACagneyCarnation::BeginPlay()
{
	Super::BeginPlay();

	CreateAnimation();

	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetOrder(ERenderingOrder::BossMonster);

	StateInit();
}

void ACagneyCarnation::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void ACagneyCarnation::CreateAnimation()
{
	Renderer->CreateAnimation("Flower_Idle", "FlowerIdle", 0.0416f);
}

void ACagneyCarnation::StateInit()
{
	State.CreateState("Idle");

	State.SetStartFunction("Idle", [this]()
		{
			Renderer->ChangeAnimation("Flower_Idle");
		});

	State.SetUpdateFunction("Idle", [this](float)
		{

		});

	State.ChangeState("Idle");
}

