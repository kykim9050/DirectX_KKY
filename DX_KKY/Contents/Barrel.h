#pragma once
#include <EngineCore/StateManager.h>

#include "MoveUnit.h"

// 설명 :
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

	float4 MoveDir = float4::Left;
	float MoveSpeed = 100.0f;

	// Intro
	int IntroRockTime = 4;
	int IntroRockCount = 0;

	// Attack 관련
	float AttackRange = 50.0f;
	float DropEndLine = 490.0f;
	int SmashTime = 8;
	int SmashCount = 0;

	// Attack After
	float BackUpSpeed = 350.0f;

private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void RendererInit();
	void AnimationInit();
	void CreateAnimation();
	void SetAnimationCallback();
	void ColliderInit();

	void DebugUpdate();

	bool PlayerNearCheck(float4 _MyPos);
	bool DropEndLineCheck(float4 _MyPos);

	// State
	void StateInit();
	void AttWait_Idle(float _DeltaTime);
	void Drop(float _DeltaTime);
	void BackUp(float _DeltaTime);
	void Normal_Idle(float _DeltaTime);
};

