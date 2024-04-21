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

	Renderer->CreateAnimation("FallDown", "Seed_Blue", 0.1f);
	Renderer->CreateAnimation("Plant", "SeedPlant_Blue", 0.1f);
	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetOrder(ERenderingOrder::Monster);

	StateInit();
}

void ASeed::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}

void ASeed::CreateSeed(ESeedColor _Color)
{
	//std::string SeedColor = "None";

	//switch (_Color)
	//{
	//case ESeedColor::Blue:
	//	SeedColor = "_Blue";
	//	break;
	//case ESeedColor::Purple:
	//	SeedColor = "_Purple";
	//	break;
	//case ESeedColor::Pink:
	//	SeedColor = "_Pink";
	//	break;
	//default:
	//	MsgBoxAssert("유효하지 않은 Seed 색입니다.");
	//	break;
	//}

	//CreateAnimation(SeedColor);
}

void ASeed::CreateAnimation(const std::string& _Color)
{
	std::string SeedFallName = "Seed" + _Color;
	std::string SeedPlantName = "SeedGrow" + _Color;


	Renderer->CreateAnimation(SeedFallName, SeedFallName, 0.1f);
	Renderer->CreateAnimation(SeedPlantName, SeedPlantName, 0.1f, false);
	Renderer->SetAutoSize(1.0f, true);
}

void ASeed::StateInit()
{
	State.CreateState("FallDown");

	State.SetStartFunction("FallDown", [this]() {
		Renderer->ChangeAnimation("FallDown");
		});
	
	State.SetUpdateFunction("FallDown", std::bind(&ASeed::FallDown, this, std::placeholders::_1));

	State.ChangeState("FallDown");
}

void ASeed::FallDown(float _DeltaTime)
{
	AddActorLocation(float4::Down * 250.0f * _DeltaTime);
}