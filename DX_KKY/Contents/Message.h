#pragma once
#include <EngineCore/Actor.h>


// ���� :
class UStateManager;
class USpriteRenderer;
class AMessage : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constrcuter destructer
	AMessage();
	~AMessage();

	// delete Function
	AMessage(const AMessage& _Other) = delete;
	AMessage(AMessage&& _Other) noexcept = delete;
	AMessage& operator=(const AMessage& _Other) = delete;
	AMessage& operator=(AMessage&& _Other) noexcept = delete;

	
	inline void SetStageEndMsg()
	{
		SetMsg(GAniName::Stage_Clear);
		State.ChangeState(GStateName::Message_Print);
	}
	inline void SetPlayerDeadMsg()
	{
		SetMsg(GAniName::PlayerDead_Message);
		State.ChangeState(GStateName::Message_Print);
	}
	inline void SetStageStartMsg()
	{
		SetMsg(GAniName::Ready_Message);
		State.ChangeState(GStateName::Message_Print);
	}

protected:

private:
	USpriteRenderer* MsgRenderer = nullptr;
	UStateManager State;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void ImageInit();
	void AnimationInit();
	void StateInit();

	std::string MsgName = "NONE";

	void SetStageEndTimeScale();
	void RecoveryTimeScale();
	void MsgPrintInitSetting();

	inline void SetMsg(std::string_view _MsgName)
	{
		MsgName = _MsgName;
	}
};

