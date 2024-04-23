#pragma once
#include "BossAttackUnit.h"
#include <EngineCore/StateManager.h>

// Ό³Έν :
class AAcorn : public ABossAttackUnit
{
	GENERATED_BODY(ABossAttackUnit)
public:
	// constrcuter destructer
	AAcorn();
	~AAcorn();

	// delete Function
	AAcorn(const AAcorn& _Other) = delete;
	AAcorn(AAcorn&& _Other) noexcept = delete;
	AAcorn& operator=(const AAcorn& _Other) = delete;
	AAcorn& operator=(AAcorn&& _Other) noexcept = delete;

	inline void Shoot()
	{
		State.ChangeState(FlowerBossState::Acorn_Fly);
		return;
	}

protected:

private:
	UStateManager State;
	float BulletSpeed = 250.0f;
	float4 ResVelocity = float4::Zero;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void StateInit() override;
	void RendererInit() override;
	void ColliderInit() override;
	void AnimationInit() override;

	void Flying(float _DeltaTime);

};

