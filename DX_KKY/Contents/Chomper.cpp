#include "PreCompile.h"

#include "Chomper.h"


AChomper::AChomper()
{
}

AChomper::~AChomper()
{
}

void AChomper::BeginPlay()
{
	Super::BeginPlay();

	AnimationInit();
	RendererInit();
	ColliderInit();
	StateInit();
}

void AChomper::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}

void AChomper::StateInit()
{
	State.CreateState("Chomp");
	State.CreateState("ChomperDeath");

	State.SetStartFunction("Chomp", [this]()
		{
			ChangeAnimation("Chomper");
		});
	State.SetStartFunction("ChomperDeath", [this]()
		{
			GetCollider()->SetActive(false);
			ChangeAnimation("ChomperDeath");
		});

	State.SetUpdateFunction("Chomp", std::bind(&AChomper::Chomp, this, std::placeholders::_1));
	State.SetUpdateFunction("ChomperDeath", [this](float) {});

	State.ChangeState("Chomp");
}

void AChomper::RendererInit()
{
	SetRendererAutoSize();
	SetRendererOrder(ERenderingOrder::Monster);
	SetRendererPivot(EPivot::BOT);
}

void AChomper::ColliderInit()
{
	SetColScale(float4(100.0f, 100.0f, 1.0f));
	SetColGroup(ECollisionGroup::Monster);
	SetColType(ECollisionType::Rect);
}

void AChomper::AnimationInit()
{
	CreateAnimation(FAniInfo("Chomper", "Chomper", 0.0416f));
	CreateAnimation(FAniInfo("ChomperDeath", "ChomperDeath", 0.0416f), false);
	
	SetRendererFrameCallback("ChomperDeath", 15, [this]()
		{
			Destroy();
		});
}

void AChomper::Chomp(float _DeltaTime)
{
	if (0 >= GetHp())
	{
		State.ChangeState("ChomperDeath");
		return;
	}
}