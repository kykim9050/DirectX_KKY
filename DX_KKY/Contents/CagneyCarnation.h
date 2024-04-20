#pragma once
#include "BossUnit.h"

enum class EAttackPattern
{
	FaceAttack_High,
	FaceAttack_Low,
	Gatling,
	CreateObject,
	Max,
};

// 설명 :
class UCollision;
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
	// 공격 패턴을 자료구조에 넣어서 관리
	// 넣어주는 패턴 이름은 각 패턴별 StateBegin이름
	template <typename EnumType>
	void InsertAttackPattern(EnumType _PatternType, std::string_view _PatternBeginName)
	{
		InsertAttackPattern(static_cast<int>(_PatternType), _PatternBeginName);
	}

	void InsertAttackPattern(int _PatternType, std::string_view _PatternBeginName)
	{
		AttackPattern.insert(std::pair(_PatternType, _PatternBeginName));
	}


private:
	// FlowerBoss의 콜리젼
	UCollision* HeadCollider = nullptr;
	UCollision* FaceAttHighCollider = nullptr;
	UCollision* FaceAttLowCollider = nullptr;


	// 페이즈가 나누어지면 map안에 key를 추가로 int 하나 더 넣어줄 수가 있음
	std::map<int, std::string> AttackPattern;

	// 페이즈1에서 상태 변화전 delay 시간
	//float P1_ChangeDelay = 5.0f;
	//float P1_ChangeDelayValue = 5.0f;
	float P1_ChangeDelay = 2.0f;
	float P1_ChangeDelayValue = 2.0f;

	// FaceAttack 지속 시간
	float FaceAttackDelay = 1.0f;
	float FaceAttackDelayValue = 1.0f;

	// Gatling 지속 시간
	float GatlingTime = 5.0f;
	float GatlingTimeValue = 5.0f;

	// CreateObject Idle 지속 시간
	float CreateObjectTime = 1.0f;

	// CreateObject Release 지속 시간
	float CreateObjectReleaseTime = 1.0f;

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
	void FaceAttackLow_Idle(float _DeltaTime);
	void Gatling_Idle(float _DeltaTime);
	void CreateObject_Idle(float _DeltaTime);
	void CreateObject_ReleaseIdle(float _DeltaTime);

	void ColliderInit();
	void CollisionCheck();

private:
	inline void GetHit(int _DmgVal)
	{
		Hp -= _DmgVal;
	}

};

