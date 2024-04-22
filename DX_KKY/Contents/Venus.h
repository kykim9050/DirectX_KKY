#pragma once
#include "BossAttackUnit.h"
#include <EngineCore/StateManager.h>

// Ό³Έν :
class AVenus : public ABossAttackUnit
{
	GENERATED_BODY(ABossAttackUnit)
public:
	// constrcuter destructer
	AVenus();
	~AVenus();

	// delete Function
	AVenus(const AVenus& _Other) = delete;
	AVenus(AVenus&& _Other) noexcept = delete;
	AVenus& operator=(const AVenus& _Other) = delete;
	AVenus& operator=(AVenus&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UStateManager State;

	void StateInit() override;
	void RendererInit() override;
	void ColliderInit() override;
	void AnimationInit() override;
};

