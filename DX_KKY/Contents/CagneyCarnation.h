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

// ���� :
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
	// ���� ������ �ڷᱸ���� �־ ����
	// �־��ִ� ���� �̸��� �� ���Ϻ� StateBegin�̸�
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
	// FlowerBoss�� �ݸ���
	UCollision* HeadCollider = nullptr;
	UCollision* FaceAttHighCollider = nullptr;
	UCollision* FaceAttLowCollider = nullptr;


	// ����� ���������� map�ȿ� key�� �߰��� int �ϳ� �� �־��� ���� ����
	std::map<int, std::string> AttackPattern;

	// ������1���� ���� ��ȭ�� delay �ð�
	//float P1_ChangeDelay = 5.0f;
	//float P1_ChangeDelayValue = 5.0f;
	float P1_ChangeDelay = 2.0f;
	float P1_ChangeDelayValue = 2.0f;

	// FaceAttack ���� �ð�
	float FaceAttackDelay = 1.0f;
	float FaceAttackDelayValue = 1.0f;

	// Gatling ���� �ð�
	float GatlingTime = 5.0f;
	float GatlingTimeValue = 5.0f;

	// CreateObject Idle ���� �ð�
	float CreateObjectTime = 1.0f;

	// CreateObject Release ���� �ð�
	float CreateObjectReleaseTime = 1.0f;

private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	// �ִϸ��̼� ����
	void AnimationInit();
	void CreateAnimation();
	void SetAnimationCallback();

	// ���� ����
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

