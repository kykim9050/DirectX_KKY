#pragma once
#include <EngineCore/StateManager.h>

#include "MonsterUnit.h"

// Ό³Έν :
class USpriteRenderer;
class UCollision;
class UDefaultSceneComponent;
class AShark : public AMonsterUnit
{
	GENERATED_BODY(AMonsterUnit)
public:
	// constrcuter destructer
	AShark();
	~AShark();

	// delete Function
	AShark(const AShark& _Other) = delete;
	AShark(AShark&& _Other) noexcept = delete;
	AShark& operator=(const AShark& _Other) = delete;
	AShark& operator=(AShark&& _Other) noexcept = delete;

protected:

private:
	//UStateManager State;

	UDefaultSceneComponent* Root = nullptr;
	USpriteRenderer* SharkRenderer = nullptr;
	USpriteRenderer* EffectRenderer = nullptr;
	UCollision* MainCollider = nullptr;

private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void RendererInit();
	void AnimationInit();
	void CreateAnimation();
	void SetAnimationCallback();
	void ColliderInit();

	// State
	void StateInit();
};

