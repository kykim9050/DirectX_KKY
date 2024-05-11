#pragma once
#include <EngineCore/StateManager.h>

#include "MonsterUnit.h"
#include "PhaseUnit.h"

// 설명 :
class UDefaultSceneComponent;
class USpriteRenderer;
class UCollision;
class ACaptainBrineybeardPhase1 : public AMonsterUnit, public UPhaseUnit
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
	int ShipAttackStartHp = 100;

	// blink
	float BlinkDelay = 4.0f;
	float BlinkDelayInit = 4.0f;

	// Cannon
	float CannonShootDelay = 3.0f;
	float CannonShootDelayInit = 3.0f;

	
	// Laugh
	int LaughNum = 5;
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

	// Wince
	int WinceTime = 4;
	int WinceCount = 0;

	// Debug
	int PatternNum = -1;
	float Dbg_PatternSwitchDelay = 0.5f;
	float Dbg_PatternSwitchDelayInit = 0.5f;

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
	void Phase1_EndSetting();

	void MoveUpAndDown(float _DeltaTime);
	void CreateWhistleEffect();
	void CreateCannonBall();
	void CreateOctopusBullet();
	void SpawnShark();
	void SpawnSeaDogs();

	// State
	void Ship_Idle(float _DeltaTime);
	void Ship_Blink(float _DeltaTime);
	void Ship_CannonShoot(float _DeltaTime);
	void Pirate_Idle(float _DeltaTime);
	void Pirate_OctoAtt_Idle(float _DeltaTime);
	void Ship_Wince(float _DeltaTime);

	// 디버그 모드
	void Dbg_ChangePattern(int _PatternNum);
	void Dbg_ChangeState();

	void PlayOctoBulletShootSound();
};

