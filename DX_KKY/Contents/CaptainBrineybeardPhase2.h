#pragma once
#include <EngineCore/StateManager.h>

#include "MonsterUnit.h"
#include "PhaseUnit.h"

// Ό³Έν :
class UDefaultSceneComponent;
class USpriteRenderer;
class UCollision;
class ACaptainBrineybeardPhase2 : public AMonsterUnit, public UPhaseUnit
{
	GENERATED_BODY(AMonsterUnit)

public:
	// constrcuter destructer
	ACaptainBrineybeardPhase2();
	~ACaptainBrineybeardPhase2();

	// delete Function
	ACaptainBrineybeardPhase2(const ACaptainBrineybeardPhase2& _Other) = delete;
	ACaptainBrineybeardPhase2(ACaptainBrineybeardPhase2&& _Other) noexcept = delete;
	ACaptainBrineybeardPhase2& operator=(const ACaptainBrineybeardPhase2& _Other) = delete;
	ACaptainBrineybeardPhase2& operator=(ACaptainBrineybeardPhase2&& _Other) noexcept = delete;

protected:

private:
	UStateManager ShipState;

	UDefaultSceneComponent* Root = nullptr;

	USpriteRenderer* ShipRenderer = nullptr;

	UCollision* MainCollider = nullptr;

private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void DebugUpdate();

	void RendererInit();
	void AnimationInit();
	void CreateAnimation();
	void SetAnimationCallback();
	void ColliderInit();

	void StateInit();
	void StateCreate();
	void StartFunctionSet();
	void UpdateFunctionSet();
	void EndFunctionSet();
};

