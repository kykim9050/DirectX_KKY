#pragma once
#include "MonsterUnit.h"
#include <EngineCore/StateManager.h>

// Ό³Έν :
class UDefaultSceneComponent;
class USpriteRenderer;
class UCollision;
class ACaptainBrineybeardPhase1 : public AMonsterUnit
{
	GENERATED_BODY(AMonsterUnit)
public:
	// constrcuter destructer
	ACaptainBrineybeardPhase1();
	~ACaptainBrineybeardPhase1();

	// delete Function
	ACaptainBrineybeardPhase1(const ACaptainBrineybeardPhase1& _Other) = delete;
	ACaptainBrineybeardPhase1(ACaptainBrineybeardPhase1&& _Other) noexcept = delete;
	ACaptainBrineybeardPhase1& operator=(const ACaptainBrineybeardPhase1& _Other) = delete;
	ACaptainBrineybeardPhase1& operator=(ACaptainBrineybeardPhase1&& _Other) noexcept = delete;

protected:

private:
	UStateManager ShipState;
	UStateManager PirateState;

	UDefaultSceneComponent* Root = nullptr;
	USpriteRenderer* PirateRenderer = nullptr;
	USpriteRenderer* PirateTopRenderer = nullptr;
	USpriteRenderer* ShipRenderer = nullptr;
	USpriteRenderer* ShipRailRenderer = nullptr;
	USpriteRenderer* ShipSailRenderer = nullptr;
	USpriteRenderer* ShipMastRenderer = nullptr;

	UCollision* MainCollider = nullptr;

	float AccTime = 0.0f;

	// blink
	float BlinkDelay = 4.0f;
	float BlinkDelayInit = 4.0f;

	// Cannon
	float CannonShootDelay = 5.0f;
	float CannonShootDelayInit = 5.0f;

	
	// Laugh
	//int LaughNum = 7;
	int LaughNum = 2;
	int LaughCount = 1;
	bool Laughing = false;

	// Octopus Attack
	float PickOctopusDelay = 3.0f;
	float PickOctopusDelayInit = 3.0f;
	float ShootDelay = 1.0f;
	float ShootDelayInit = 1.0f;
	int ShootNum = 2;
	int ShootCount = 1;

	// Whistling
	float WhistleDelay = 5.0f;
	float WhistleDelayInit = 5.0f;

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

	void MoveUpAndDown(float _DeltaTime);
	void CreateWhistleEffect();
	void CreateCannonBall();
	void CreateOctopusBullet();

	// State
	void Ship_Idle(float _DeltaTime);
	void Ship_Blink(float _DeltaTime);
	void Ship_CannonShoot(float _DeltaTime);
	void Pirate_Idle(float _DeltaTime);
	void Pirate_OctoAtt_Idle(float _DeltaTime);
	void Ship_Wince(float _DeltaTime);
};

