#pragma once
#include "BossAttackUnit.h"
#include <EngineCore/StateManager.h>

// ���� :
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
	float4 BoundaryValue = float4::Zero;
	float4 Velocity = float4::Zero;
	float Speed = 100.0f;

	void StateInit() override;
	void RendererInit() override;
	void ColliderInit() override;
	void AnimationInit() override;

	void Flying(float _DeltaTime);
};

