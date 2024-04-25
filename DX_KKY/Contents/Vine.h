#pragma once
#include "BossAttackUnit.h"
#include <EngineCore/StateManager.h>

// ���� :
class USpriteRenderer;
class UCollision;
class AVine : public ABossAttackUnit
{
	GENERATED_BODY(ABossAttackUnit)
public:
	// constrcuter destructer
	AVine();
	~AVine();

	// delete Function
	AVine(const AVine& _Other) = delete;
	AVine(AVine&& _Other) noexcept = delete;
	AVine& operator=(const AVine& _Other) = delete;
	AVine& operator=(AVine&& _Other) noexcept = delete;

	inline void GrowUp()
	{
		State.ChangeState(FlowerBossState::Vine_GrowUp);
		return;
	}
	inline bool IsWait() const
	{
		if (FlowerBossState::Vine_Wait == State.GetCurStateName())
		{
			return true;
		}

		return false;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UStateManager State;
	USpriteRenderer* BackVineRenderer;
	UCollision* StemCollider;

	float AttackDelay = 0.0f;

	void StateInit() override;
	void RendererInit() override;
	void ColliderInit() override;
	void AnimationInit() override;

	void WaitAttack(float _DeltaTime);
};

