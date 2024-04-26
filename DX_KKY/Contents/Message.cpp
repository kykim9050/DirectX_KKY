#include "PreCompile.h"
#include <EngineCore/StateManager.h>
#include <EngineCore/SpriteRenderer.h>

#include "Message.h"

AMessage::AMessage()
{
	MsgRenderer = CreateDefaultSubObject<USpriteRenderer>("MsgRenderer");
	SetRoot(MsgRenderer);
}

AMessage::~AMessage()
{
}

void AMessage::BeginPlay()
{
	Super::BeginPlay();

	ImageInit();
	AnimationInit();
	StateInit();
}

void AMessage::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}

void AMessage::ImageInit()
{
	MsgRenderer->SetOrder(ERenderingOrder::Message);
	MsgRenderer->SetPosition(float4(640.0f, -360.0f, 0.0f));
	MsgRenderer->SetScale(GEngine->EngineWindow.GetWindowScale());
}

void AMessage::AnimationInit()
{
	MsgRenderer->CreateAnimation("Ready_Message", "ReadyWALLOP!", 0.0416f, false);
	MsgRenderer->CreateAnimation("PlayerDead_Message", "YouDied", 0.0416f, false);
	MsgRenderer->CreateAnimation("Stage_Clear", "Knockout", 0.0416f, false);

	MsgRenderer->SetFrameCallback("Ready_Message", 50,[this]()
		{
			Destroy();
		});
	MsgRenderer->SetFrameCallback("PlayerDead_Message", 8, [this]()
		{
			Destroy();
		});
	MsgRenderer->SetFrameCallback("Stage_Clear", 35, [this]()
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
			if ("NONE" == MsgName)
			{
				MsgBoxAssert("MSG 애니메이션 이름이 지정되지 않았습니다.");
				return;
			}

			MsgRenderer->ChangeAnimation(MsgName);
		});

	State.SetUpdateFunction("Message_Init", [this](float)
		{
			State.ChangeState("Message_Print");
			return;
		});
	State.SetUpdateFunction("Message_Print", [](float) {});

	State.ChangeState("Message_Init");
}