#pragma once
#include <EngineCore/StateManager.h>

#include "MonsterUnit.h"
#include "PhaseUnit.h"

// ���� :
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
	// Lazar ����
	int ChargingTime = 10;
	int ChargingCount = 0;
	float LazarShootDelay = 5.0f;
	float LazarShootDelayInit = 5.0f;
	int LazarAttTime = 17;
	int LazarAttCount = 0;


	// transforming ����
	int RoarTime = 22;
	int RoarCount = 0;

	// bubble shot ����
	float BubbleShootDelay = 2.0f;
	float BubbleShootDelayInit = 2.0f;

	// Dead ����
	float ExplosionEffDelay = 0.4f;
	float ExplosionEffDelayInit = 0.4f;

	UStateManager ShipState;

	UDefaultSceneComponent* Root = nullptr;

	USpriteRenderer* ShipRenderer = nullptr;
	USpriteRenderer* JawRenderer = nullptr;
	USpriteRenderer* UvulaRenderer = nullptr;
	USpriteRenderer* LazarRenderer = nullptr;

	UCollision* LazarCollider = nullptr;
	UCollision* MainCollider = nullptr;


private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void AfterHitFlash() override;

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

	void Ship_Idle(float _DeltaTime);

	void CreateUvulaBubble();
	void Dead(float _DeltaTime);

	void PlayShootBubbleSound();
};

