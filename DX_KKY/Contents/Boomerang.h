#pragma once
#include "BossAttackUnit.h"
#include <EngineCore/StateManager.h>

// Ό³Έν :
class ABoomerang : public ABossAttackUnit
{
	GENERATED_BODY(ABossAttackUnit)
public:
	// constrcuter destructer
	ABoomerang();
	~ABoomerang();

	// delete Function
	ABoomerang(const ABoomerang& _Other) = delete;
	ABoomerang(ABoomerang&& _Other) noexcept = delete;
	ABoomerang& operator=(const ABoomerang& _Other) = delete;
	ABoomerang& operator=(ABoomerang&& _Other) noexcept = delete;

	inline void Throw()
	{
		State.ChangeState(FlowerBossState::Boomerang_Throw);
		return;
	}

protected:

private:
	UStateManager State;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void StateInit() override;
	void RendererInit() override;
	void ColliderInit() override;
	void AnimationInit() override;
};

