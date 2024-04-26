#pragma once
#include <EngineCore/Actor.h>


// Ό³Έν :
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

	inline void SetMsg(std::string_view _MsgName)
	{
		MsgName = _MsgName;
	}
	inline void SetStageEndMsg()
	{
		MsgName = GAniName::Stage_Clear;
	}
	inline void SetPlayerDeadMsg()
	{
		MsgName = GAniName::PlayerDead_Message;
	}
	inline void SetStageStartMsg()
	{
		MsgName = GAniName::Ready_Message;
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
};

