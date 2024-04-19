#pragma once
#include "BossUnit.h"

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
};

