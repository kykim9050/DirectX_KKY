#pragma once
#include <EngineCore/StateManager.h>

#include "MoveUnit.h"

// Ό³Έν :
class UCollision;
class UDefaultSceneComponent;
class USpriteRenderer;
class ABarrel : public UMoveUnit
{
	GENERATED_BODY(UMoveUnit)
public:
	// constrcuter destructer
	ABarrel();
	~ABarrel();

	// delete Function
	ABarrel(const ABarrel& _Other) = delete;
	ABarrel(ABarrel&& _Other) noexcept = delete;
	ABarrel& operator=(const ABarrel& _Other) = delete;
	ABarrel& operator=(ABarrel&& _Other) noexcept = delete;

protected:

private:
	UStateManager State;

	UDefaultSceneComponent* Root = nullptr;
	USpriteRenderer* BarrelRenderer = nullptr;
	USpriteRenderer* DustRenderer = nullptr;
	USpriteRenderer* EffectRenderer = nullptr;
	UCollision* MainCollider = nullptr;


	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void RendererInit();
	void AnimationInit();
	void CreateAnimation();
	void SetAnimationCallback();
	void ColliderInit();

	void StateInit();

	// State
	void AttWait_Idle(float _DeltaTime);
};

