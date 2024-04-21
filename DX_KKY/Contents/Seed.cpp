#include "PreCompile.h"
#include <EngineCore/StateManager.h>

#include "Seed.h"

ASeed::ASeed()
{
}

ASeed::~ASeed()
{
}

void ASeed::BeginPlay()
{
	Super::BeginPlay();

	CreateSeedAnimation();
	ColliderInit();

	StateInit();
}

void ASeed::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}

void ASeed::StateInit()
{
	State.CreateState("Fall");
	State.CreateState("Plant");
	State.CreateState("GrowUp");

	State.SetStartFunction("Fall", [this]() {
		Renderer->ChangeAnimation("Fall");
		});
	State.SetStartFunction("Plant", [this]() {
		Collider->SetActive(false);
		Renderer->ChangeAnimation("Plant");
		});
	State.SetStartFunction("GrowUp", [this]() {
		Renderer->ChangeAnimation("GrowUp");
		});


	
	State.SetUpdateFunction("Fall", std::bind(&ASeed::Fall, this, std::placeholders::_1));
	State.SetUpdateFunction("Plant", std::bind(&ASeed::Plant, this, std::placeholders::_1));
	State.SetUpdateFunction("GrowUp", std::bind(&ASeed::GrowUp, this, std::placeholders::_1));


	State.ChangeState("Fall");
}

void ASeed::Fall(float _DeltaTime)
{
	if (-620.0f >= GetActorLocation().Y)
	{
		State.ChangeState("Plant");
		return;
	}

	AddActorLocation(float4::Down * 250.0f * _DeltaTime);
}

void ASeed::CreateSeedAnimation()
{
	Renderer->CreateAnimation("Fall", "Seed_Blue", 0.1f);
	Renderer->CreateAnimation("Plant", "SeedPlant_Blue", 0.1f, false);
	Renderer->CreateAnimation("GrowUp", "Vine", 0.1f, false);

	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetOrder(ERenderingOrder::Monster);
	Renderer->SetPivot(EPivot::BOT);

	{
		Renderer->SetFrameCallback("Plant", 10, [this]()
			{
				State.ChangeState("GrowUp");
				return;
			});
	}
}

void ASeed::ColliderInit()
{
	float4 ColliderPos = GetActorLocation();
	ColliderPos.Y += 20.0f;

	Collider->SetScale(float4(20.0f, 40.0f, 1.0f));
	Collider->SetPosition(ColliderPos);
	Collider->SetCollisionGroup(ECollisionGroup::Monster);
	Collider->SetCollisionType(ECollisionType::Rect);
}

void ASeed::Plant(float _DeltaTime)
{

}

void ASeed::GrowUp(float _DeltaTime)
{

}