#pragma once
#include "BossAttackUnit.h"
#include <EngineCore/StateManager.h>

// Ό³Έν :
class AChomper : public ABossAttackUnit
{
	GENERATED_BODY(ABossAttackUnit)
public:
	// constrcuter destructer
	AChomper();
	~AChomper();

	// delete Function
	AChomper(const AChomper& _Other) = delete;
	AChomper(AChomper&& _Other) noexcept = delete;
	AChomper& operator=(const AChomper& _Other) = delete;
	AChomper& operator=(AChomper&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UStateManager State;

	void StateInit() override;
	void RendererInit() override;
	void ColliderInit() override;
	void AnimationInit() override;

	void Chomp(float _DeltaTime);
};

