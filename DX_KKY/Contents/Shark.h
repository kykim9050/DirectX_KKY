#pragma once
#include <EngineCore/StateManager.h>

#include "MonsterUnit.h"

// ���� :
class UEngineSoundPlayer;
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
	UStateManager State;

	UDefaultSceneComponent* Root = nullptr;
	USpriteRenderer* SharkRenderer = nullptr;
	USpriteRenderer* FinRenderer = nullptr;
	USpriteRenderer* EffectRenderer = nullptr;
	UCollision* MainCollider = nullptr;

	UEngineSoundPlayer LeaveSound = UEngineSoundPlayer();

private:
	float AppearIntroSpeed = 500.0f;
	float FinMoveBoundaryValue = -800.0f;
	float AttackSpeed = 1100.0f;
	float LeaveSpeed = 250.0f;

private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void RendererInit();
	void AnimationInit();
	void CreateAnimation();
	void SetAnimationCallback();
	void ColliderInit();
	void DebugUpdate();


	// State
	void StateInit();
	void Appear_Intro(float _DeltaTime);
	void Appear(float _DeltaTime);
	void Chomp(float _DeltaTime);
	void Leave(float _DeltaTime);

};

