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
	MsgRenderer->SetPosition(GRendererPos::Msg_InitPos);
	MsgRenderer->SetScale(GEngine->EngineWindow.GetWindowScale());
}

void AMessage::AnimationInit()
{
	MsgRenderer->CreateAnimation(GAniName::Ready_Message, GSpriteName::Ready_Message, 0.0416f, false);
	MsgRenderer->CreateAnimation(GAniName::PlayerDead_Message, GSpriteName::PlayerDead_Message, 0.0416f, false);
	MsgRenderer->CreateAnimation(GAniName::Stage_Clear, GSpriteName::Stage_Clear, 0.0416f, false);

	MsgRenderer->SetFrameCallback(GAniName::Ready_Message, 50,[this]()
		{
			Destroy();
		});
	MsgRenderer->SetFrameCallback(GAniName::PlayerDead_Message, 8, [this]()
		{
			Destroy();
		});
	MsgRenderer->SetFrameCallback(GAniName::Stage_Clear, 35, [this]()
		{
			UContentsFunction::GetStagePlayer()->InputOn();
			RecoveryTimeScale();
			Destroy();
		});
}

void AMessage::StateInit()
{
	State.CreateState(GStateName::Message_Init);
	State.CreateState(GStateName::Message_Print);

	
	State.SetStartFunction(GStateName::Message_Init, []() {});
	State.SetStartFunction(GStateName::Message_Print, [this]()
		{
			if (GAniName::Stage_Clear != MsgName
				&& GAniName::Ready_Message != MsgName
				&& GAniName::PlayerDead_Message != MsgName
				)
			{
				MsgBoxAssert("MSG 애니메이션 이름이 지정되지 않았습니다.");
				return;
			}

			MsgPrintInitSetting();
			MsgRenderer->ChangeAnimation(MsgName);
		});

	State.SetUpdateFunction(GStateName::Message_Init, [this](float)
		{
			State.ChangeState(GStateName::Message_Print);
			return;
		});
	State.SetUpdateFunction(GStateName::Message_Print, [](float) {});

	State.ChangeState(GStateName::Message_Init);
}

void AMessage::SetStageEndTimeScale()
{
	for (int i = 0; i < static_cast<int>(EActorType::Max); i++)
	{
		if (static_cast<int>(EActorType::FilmEffect) == i
			|| static_cast<int>(EActorType::ScreenMsg) == i
			)
		{
			continue;
		}
		GEngine->SetOrderTimeScale(i, 0.0f);
	}
}

void AMessage::RecoveryTimeScale()
{
	for (int i = 0; i < static_cast<int>(EActorType::Max); i++)
	{
		GEngine->SetOrderTimeScale(i, 1.0f);
	}
}

void AMessage::MsgPrintInitSetting()
{
	if (GAniName::Stage_Clear == MsgName)
	{
		UContentsFunction::GetStagePlayer()->InputOff();
		SetStageEndTimeScale();
		return;
	}
	else if (GAniName::Ready_Message == MsgName)
	{
		return;
	}
	else if (GAniName::PlayerDead_Message == MsgName)
	{

		return;
	}
	else
	{
		MsgBoxAssert("유효하지 않은 메세지 이미지입니다.");
		return;
	}
}