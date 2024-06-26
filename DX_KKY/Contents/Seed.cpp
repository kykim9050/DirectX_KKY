#include "PreCompile.h"
#include <EngineCore/StateManager.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>

#include "Seed.h"
#include "Chomper.h"
#include "Venus.h"
#include "MiniFlower.h"

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
	State.CreateState("Init");
	State.CreateState("Fall");
	State.CreateState("Plant");

	State.SetStartFunction("Fall", [this]() {
		Renderer->ChangeAnimation("Fall");
		});
	State.SetStartFunction("Plant", [this]() {
		Collision->SetActive(false);
		Renderer->ChangeAnimation("Plant");
		});

	State.SetUpdateFunction("Init", [this](float)
		{
			State.ChangeState("Fall");
			return;
		});
	State.SetUpdateFunction("Fall", std::bind(&ASeed::Fall, this, std::placeholders::_1));
	State.SetUpdateFunction("Plant", std::bind(&ASeed::Plant, this, std::placeholders::_1));

	State.SetEndFunction("Init", [this]()
		{
			if (ESeedColor::Pink == Color)
			{
				SetParryableObject();
			}
			AnimationInit();
			RendererInit();
		});

	State.ChangeState("Init");
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

	std::string SeedColor = "";
	std::string FallAniName = "SeedFall";
	std::string PlantAniName = "SeedPlant";

	switch (Color)
	{
	case ESeedColor::Blue:
		SeedColor = "_Blue";
		break;
	case ESeedColor::Purple:
		SeedColor = "_Purple";
		break;
	case ESeedColor::Pink:
		SeedColor = "_Pink";
		break;
	default:
		MsgBoxAssert("씨앗의 색을 지정해주십시오.. 제발...");
		return;
	}

	FallAniName = FallAniName + SeedColor;
	PlantAniName = PlantAniName + SeedColor;

	Renderer->CreateAnimation(FlowerBossAniName::SeedFall, FallAniName, 0.1f);
	Renderer->CreateAnimation(FlowerBossAniName::SeedPlant, PlantAniName, 0.1f, false);
	Renderer->CreateAnimation(FlowerBossAniName::SeedGrowUpBegin, "VineGrowBurst", { 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f , 0.1f }, { 0, 1, 2, 1, 0, 1, 2, 3, 4, 5, 6 }, false);

	{
		Renderer->SetFrameCallback(FlowerBossAniName::SeedPlant, 10, [this]()
			{
				Renderer->ChangeAnimation(FlowerBossAniName::SeedGrowUpBegin);
			});
		Renderer->SetFrameCallback(FlowerBossAniName::SeedGrowUpBegin, 8, [this]()
			{
				switch (Color)
				{
				case ESeedColor::Blue:
				{
					UEngineSoundPlayer Sound = UEngineSound::SoundPlay("sfx_flower_venus_vine_grow_medium.wav");
					Sound.SetVolume(0.3f);

					VineRenderer->ChangeAnimation(FlowerBossAniName::VineGrowUp);
					break;
				}
				case ESeedColor::Purple:
				{
					// chomper 생성
					CreateChomper();
					break;
				}
				case ESeedColor::Pink:
				{
					UEngineSoundPlayer Sound = UEngineSound::SoundPlay("sfx_flower_venus_vine_grow_medium.wav");
					Sound.SetVolume(0.3f);

					VineRenderer->ChangeAnimation(FlowerBossAniName::VineGrowUp);
					break;
				}
				default:
					MsgBoxAssert("아직 색이 지정되지 않은 씨앗입니다.");
					return;
				}

			});
		Renderer->SetFrameCallback(FlowerBossAniName::SeedGrowUpBegin, 11, [this]()
			{
				Renderer->SetActive(false);

				switch (Color)
				{
				case ESeedColor::Blue:
				case ESeedColor::Pink:
					break;
				case ESeedColor::Purple:
				{
					Destroy();
					break;
				}
				default:
					MsgBoxAssert("아직 색이 지정되지 않은 씨앗입니다.");
					return;
				}

			});

		VineRenderer->SetFrameCallback(FlowerBossAniName::VineGrowUp, 13, [this]()
			{
				switch (Color)
				{
				case ESeedColor::Blue:
					CreateVenus();
					break;
				case ESeedColor::Pink:
					CreateMiniFlower();
					break;
				default:
					MsgBoxAssert("VineGrowUp에서 생성될 수 없는 씨앗 색입니다.");
					return;
				}
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
	VineRenderer->SetOrder(ERenderingOrder::Monster2);
	VineRenderer->SetPivot(EPivot::BOT);

	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetOrder(ERenderingOrder::Monster1);
	Renderer->SetPivot(EPivot::BOT);
}

void ASeed::ColliderInit()
{
	float4 ColliderPos = GetActorLocation();
	ColliderPos.Y += ColliderYOffset;

	Collision->SetScale(FlowerBossStageValue::SeedColliderScale);
	Collision->SetPosition(ColliderPos);
	Collision->SetCollisionGroup(ECollisionGroup::MonsterBullet);
	Collision->SetCollisionType(ECollisionType::Rect);
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
	case ESeedColor::Purple:
	case ESeedColor::Pink:
		break;
	default:
		MsgBoxAssert("지정되지 않은 씨앗 색입니다.");
		return;
	}

	Color = _Color;
}

void ASeed::CreateChomper()
{
	std::shared_ptr<AChomper> Chomper = GetWorld()->SpawnActor<AChomper>("Chomper");
	Chomper->SetActorLocation(GetActorLocation());
	Chomper->SetColPosition(float4(0.0f, GColliderScale::Chomper_ColScale.hY(), 0.0f));
}

void ASeed::CreateVenus()
{
	float4 InitPos = GetActorLocation();
	InitPos.Y += 235.0f;

	float RandomDegree = UMath::RandomReturnFloat(-45.0f, 0.0f);

	std::shared_ptr<AVenus> Venus = GetWorld()->SpawnActor<AVenus>("Venus");
	Venus->SetActorLocation(InitPos);
	Venus->SetActorRotation(float4(0.0f, 0.0f, RandomDegree));
	Venus->SetColPosition(float4(0.0f, 0.0f/*GColliderScale::Venus_ColScale.hY()*/, 0.0f));
}

void ASeed::CreateMiniFlower()
{
	float4 InitPos = GetActorLocation();
	InitPos.Y += 235.0f;

	std::shared_ptr<AMiniFlower> MiniFlower = GetWorld()->SpawnActor<AMiniFlower>("MiniFlower");
	MiniFlower->SetActorLocation(InitPos);
}