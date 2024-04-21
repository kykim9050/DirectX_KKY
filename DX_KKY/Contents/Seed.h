#pragma once
#include "BossAttackUnit.h"

// Ό³Έν :
class UStateManager;
class ASeed : public ABossAttackUnit
{
	GENERATED_BODY(ABossAttackUnit)
public:
	// constrcuter destructer
	ASeed();
	~ASeed();

	// delete Function
	ASeed(const ASeed& _Other) = delete;
	ASeed(ASeed&& _Other) noexcept = delete;
	ASeed& operator=(const ASeed& _Other) = delete;
	ASeed& operator=(ASeed&& _Other) noexcept = delete;

	void CreateSeed(ESeedColor _Color);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UStateManager State = UStateManager();

	void StateInit();
	void CreateAnimation(const std::string& _Color);
	void FallDown(float _DeltaTime);


};

