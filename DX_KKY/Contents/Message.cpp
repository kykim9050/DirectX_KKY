#include "PreCompile.h"
#include <EngineCore/StateManager.h>
#include <EngineCore/Image.h>

#include "Message.h"

AMessage::AMessage()
{
	Message = CreateWidget<UImage>(GetWorld(), "Message");
}

AMessage::~AMessage()
{
}

void AMessage::BeginPlay()
{
	Super::BeginPlay();

	AnimationInit();
	ImageInit();
	StateInit();
}

void AMessage::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}

void AMessage::ImageInit()
{
	Message = CreateWidget<UImage>(GetWorld(), "Message");
	Message->AddToViewPort(ERenderingOrder::Message);
	Message->SetPosition(float4(0.0f, 0.0f, 0.0f));
	Message->SetScale(GEngine->EngineWindow.GetWindowScale());
}

void AMessage::AnimationInit()
{
	Message->CreateAnimation("Ready_Message", "ReadyWALLOP!", 0.0416f, false);
	Message->CreateAnimation("PlayerDead_Message", "YouDied", 0.0416f, false);
	Message->CreateAnimation("Stage_Clear", "Knockout", 0.0416f, false);

	Message->SetFrameCallback("Ready_Message", 50,[this]()
		{
			Destroy();
		});
	Message->SetFrameCallback("PlayerDead_Message", 8, [this]()
		{
			Destroy();
		});
	Message->SetFrameCallback("Stage_Clear", 35, [this]()
		{
			Destroy();
		});
}

void AMessage::StateInit()
{
	State.CreateState("Message_Init");
	State.CreateState("Message_Print");

	
	State.SetStartFunction("Message_Init", []() {});
	State.SetStartFunction("Message_Print", [this]()
		{

		});

	State.SetUpdateFunction("Message_Init", [this](float)
		{
			State.ChangeState("Message_Print");
			return;
		});
	State.SetUpdateFunction("Message_Print", [](float) {});

	State.ChangeState("Message_Init");
}