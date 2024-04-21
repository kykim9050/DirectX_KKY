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

	AnimationInit();
	RendererInit();
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
	if (SeedFallEndValue >= GetActorLocation().Y)
	{
		State.ChangeState("Plant");
		return;
	}

	AddActorLocation(float4::Down * SeedFallSpeed * _DeltaTime);
}

void ASeed::AnimationInit()
{
	VineRenderer->CreateAnimation(FlowerBossAniName::VineGrowUp, "Vine", 0.1f, false);
	VineRenderer->CreateAnimation(FlowerBossAniName::VineDisappear, "VineGrowBurst", 0.1f, false, 3, 6);

	Renderer->CreateAnimation(FlowerBossAniName::SeedFall, "Seed_Blue", 0.1f);
	Renderer->CreateAnimation(FlowerBossAniName::SeedPlant, "SeedPlant_Blue", 0.1f, false);
	Renderer->CreateAnimation(FlowerBossAniName::SeedGrowUpBegin, "VineGrowBurst", { 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f , 0.1f }, { 0, 1, 2, 1, 0, 1, 2, 3, 4, 5, 6 }, false);

	{
		Renderer->SetFrameCallback(FlowerBossAniName::SeedPlant, 10, [this]()
			{
				Renderer->ChangeAnimation(FlowerBossAniName::SeedGrowUpBegin);
			});
		Renderer->SetFrameCallback(FlowerBossAniName::SeedGrowUpBegin, 8, [this]()
			{
				VineRenderer->ChangeAnimation(FlowerBossAniName::VineGrowUp);
			});
		Renderer->SetFrameCallback(FlowerBossAniName::SeedGrowUpBegin, 11, [this]()
			{
				Renderer->SetActive(false);
			});

		VineRenderer->SetFrameCallback(FlowerBossAniName::VineGrowUp, 36, [this]()
			{
				VineRenderer->ChangeAnimation(FlowerBossAniName::VineDisappear);
			});
		VineRenderer->SetFrameCallback(FlowerBossAniName::VineDisappear, 4, [this]()
			{
				Destroy();
			});
	}
}

void ASeed::RendererInit()
{
	VineRenderer->SetAutoSize(1.0f, true);
	VineRenderer->SetOrder(ERenderingOrder::Monster);
	VineRenderer->SetPivot(EPivot::BOT);

	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetOrder(ERenderingOrder::Monster);
	Renderer->SetPivot(EPivot::BOT);
}

void ASeed::ColliderInit()
{
	float4 ColliderPos = GetActorLocation();
	ColliderPos.Y += ColliderYOffset;

	Collider->SetScale(FlowerBossStageValue::SeedColliderScale);
	Collider->SetPosition(ColliderPos);
	Collider->SetCollisionGroup(ECollisionGroup::MonsterBullet);
	Collider->SetCollisionType(ECollisionType::Rect);
}

void ASeed::Plant(float _DeltaTime)
{

}

void ASeed::GrowUp(float _DeltaTime)
{

}

void ASeed::SetColor(ESeedColor _Color)
{
	switch (_Color)
	{
	case ESeedColor::Blue:
		break;
	case ESeedColor::Purple:
		break;
	case ESeedColor::Pink:
		break;
	default:
		MsgBoxAssert("�������� ���� ���� ���Դϴ�.");
		return;
	}
}