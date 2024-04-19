#pragma once
#include "BossUnit.h"

enum class Phase1_AttackPattern
{
	FaceAttack_High,
	Max,
};

// 설명 :
class ACagneyCarnation : public ABossUnit
{
	GENERATED_BODY(ABossUnit)

public:
	// constrcuter destructer
	ACagneyCarnation();
	~ACagneyCarnation();

	// delete Function
	ACagneyCarnation(const ACagneyCarnation& _Other) = delete;
	ACagneyCarnation(ACagneyCarnation&& _Other) noexcept = delete;
	ACagneyCarnation& operator=(const ACagneyCarnation& _Other) = delete;
	ACagneyCarnation& operator=(ACagneyCarnation&& _Other) noexcept = delete;

protected:

private:
	// 페이즈1에서 상태 변화전 delay 시간
	float P1_ChangeDelay = 5.0f;
	float P1_ChangeDelayValue = 5.0f;

	// FaceAttack 지속 시간
	float FaceAttackDelay = 1.0f;
	float FaceAttackDelayValue = 1.0f;

private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	// 애니메이션 관련
	void AnimationInit();
	void CreateAnimation();
	void SetAnimationCallback();

	// 상태 관련
	void StateInit() override;
	void StateCreate();
	void StartFunctionSet();
	void UpdateFunctionSet();
	void EndFunctionSet();

	void Idle(float _DeltaTime);
	void FaceAttackHigh_Idle(float _DeltaTime);
};

