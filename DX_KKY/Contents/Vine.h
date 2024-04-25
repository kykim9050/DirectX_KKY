#pragma once
#include "BossAttackUnit.h"
#include <EngineCore/StateManager.h>

// Ό³Έν :
class USpriteRenderer;
class Vine : public ABossAttackUnit
{
	GENERATED_BODY(ABossAttackUnit)
public:
	// constrcuter destructer
	Vine();
	~Vine();

	// delete Function
	Vine(const Vine& _Other) = delete;
	Vine(Vine&& _Other) noexcept = delete;
	Vine& operator=(const Vine& _Other) = delete;
	Vine& operator=(Vine&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UStateManager State;
	USpriteRenderer* BackVineRenderer;

	void StateInit() override;
	void RendererInit() override;
	void ColliderInit() override;
	void AnimationInit() override;
};

