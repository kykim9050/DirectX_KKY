#include "PreCompile.h"
#include <EngineCore/StateManager.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>

#include "Seed.h"


ASeed::ASeed()
{
	VineRenderer = CreateDefaultSubObject<USpriteRenderer>("VineRenderer");
	VineRenderer->SetupAttachment(Root);
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

	State.SetStartFunction("Fall", [this]() {
		Renderer->ChangeAnimation("Fall");
		});
	State.SetStartFunction("Plant", [this]() {
		Collider->SetActive(false);
		Renderer->ChangeAnimation("Plant");
		});

	State.SetUpdateFunction("Fall", std::bind(&ASeed::Fall, this, std::placeholders::_1));
	State.SetUpdateFunction("Plant", std::bind(&ASeed::Plant, this, std::placeholders::_1));

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
	VineRenderer->CreateAnimation("VineGrowUp", "Vine", 0.1f, false);
	VineRenderer->CreateAnimation("VineDisappear", "VineGrowBurst", 0.1f, false, 3, 6);
	VineRenderer->SetAutoSize(1.0f, true);
	VineRenderer->SetOrder(ERenderingOrder::Monster);
	VineRenderer->SetPivot(EPivot::BOT);

	Renderer->CreateAnimation("Fall", "Seed_Blue", 0.1f);
	Renderer->CreateAnimation("Plant", "SeedPlant_Blue", 0.1f, false);
	Renderer->CreateAnimation("GrowUpBegin", "VineGrowBurst", { 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f , 0.1f }, { 0, 1, 2, 1, 0, 1, 2, 3, 4, 5, 6 }, false);

	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetOrder(ERenderingOrder::Monster);
	Renderer->SetPivot(EPivot::BOT);

	{
		Renderer->SetFrameCallback("Plant", 10, [this]()
			{
				Renderer->ChangeAnimation("GrowUpBegin");
			});
		Renderer->SetFrameCallback("GrowUpBegin", 8, [this]()
			{
				VineRenderer->ChangeAnimation("VineGrowUp");
			});
		Renderer->SetFrameCallback("GrowUpBegin", 11, [this]()
			{
				Renderer->SetActive(false);
			});

		VineRenderer->SetFrameCallback("VineGrowUp", 36, [this]()
			{
				VineRenderer->ChangeAnimation("VineDisappear");
			});
		VineRenderer->SetFrameCallback("VineDisappear", 4, [this]()
			{
				VineRenderer->SetActive(false);
				// ������ �ϴ� ������, �ݸ����� Off�� ����,
				// �ش� ���Ϳ��� ������ ���Ͱ� �ױ����� �ش� ���Ͱ� ��ȯ�Ǹ� ���� ���� ������ ����
				// �ٵ� �������� �����ϴϱ� �׳� Destroy�ص� ���� ������?
				Destroy();
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