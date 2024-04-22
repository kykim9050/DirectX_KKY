#pragma once
#include "BossAttackUnit.h"
#include <EngineCore/StateManager.h>

// Ό³Έν :
class AMiniFlower : public ABossAttackUnit
{
	GENERATED_BODY(ABossAttackUnit)
public:
	// constrcuter destructer
	AMiniFlower();
	~AMiniFlower();

	// delete Function
	AMiniFlower(const AMiniFlower& _Other) = delete;
	AMiniFlower(AMiniFlower&& _Other) noexcept = delete;
	AMiniFlower& operator=(const AMiniFlower& _Other) = delete;
	AMiniFlower& operator=(AMiniFlower&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UStateManager State = UStateManager();

	void StateInit() override;
	void RendererInit() override;
	void ColliderInit() override;
	void AnimationInit() override;

	void Flying(float _DeltaTime);
};

