#pragma once
#include "BossAttackUnit.h"
#include <EngineCore/StateManager.h>

// Ό³Έν :
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

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UStateManager State;
	USpriteRenderer* BackVineRenderer;
	UCollision* StemCollider;

	void StateInit() override;
	void RendererInit() override;
	void ColliderInit() override;
	void AnimationInit() override;
};

