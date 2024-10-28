#pragma once
#include "BossUnit.h"
#include "PhaseUnit.h"

enum class EAttackPattern
{
	FaceAttack_High,
	FaceAttack_Low,
	Gatling,
	CreateObject,
	Max,
};

// ���� :
class USpriteRenderer;
class UCollision;
class AAcorn;
class AVine;
class ACagneyCarnation : public ABossUnit, public UPhaseUnit
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

	// FlowerBoss�� ������
	USpriteRenderer* BottomIvyRenderer = nullptr;

	// FlowerBoss�� �ݸ���
	UCollision* HeadCollider = nullptr;
	UCollision* FaceAttHighCollider = nullptr;
	UCollision* FaceAttLowCollider = nullptr;
	UCollision* BottomIvyCollider = nullptr;

	// ��Ʋ�� ���Ͽ��� �����ϴ� Seed�� ��
	const int SeedNum = 5;

	// ����� ���������� map�ȿ� key�� �߰��� int �ϳ� �� �־��� ���� ����
	std::map<int, std::string> AttackPattern;

	// ������1���� ���� ��ȭ�� delay �ð�
	float P1_ChangeDelay = 5.0f;
	float P1_ChangeDelayValue = 5.0f;
	//float P1_ChangeDelay = 2.0f;
	//float P1_ChangeDelayValue = 2.0f;

	// FaceAttack ���� �ð�
	float FaceAttackDelay = 1.0f;
	float FaceAttackDelayValue = 1.0f;

	// Gatling ���� �ð�
	float GatlingTime = 5.0f;
	float GatlingTimeValue = 5.0f;

	// CreateObject Idle ���� �ð�
	float CreateObjectTime = 0.5f;
	float CreateObjectTimeInit = 0.5f;

	// CreateObject Release ���� �ð�
	float CreateObjectReleaseTime = 1.0f;

	// MissileLaunchTIme
	float MissileLaunchTIme = 0.0f;
	float MissileLaunchTImeValue = 0.3f;

	// Createobject ����
	const int AcornNum = 3;
	float CreateObjectDelay = 0.0f;
	float CreateObjectDelayInit = 0.0f;

	// Phase2 ��ȭ ����
	int Phase2StartHP = 100;
	float P2ChangeDelay = 0.5f;
	float P2ChangingDelay = 1.0f;

	// Phase2 VineAttack ����
	int VineNum = 3;
	std::vector<AVine*> Vines = std::vector<AVine*>();
	bool CanCreateVine = false;
	float VineAttackDelay = 0.0f;
	float VineAttackDelayInit = 5.0f;

	// Phase2 Spit ����
	float SpitDelay = 6.0f;
	float SpitDelayInit = 6.0f;

	// Dead ����
	float ExplosionEffDelay = 0.4f;
	float ExplosionEffDelayInit = 0.4f;

private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void DebugUpdate();

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
	void Phase2Intro_1(float _DeltaTime);
	void Phase2Intro_2(float _DeltaTime);
	void Phase2_Idle(float _DeltaTime);
	void Dead(float _DeltaTime);

	void ColliderInit();
	void RendererInit();

	void CreateAcorn();
	void CreateObjectSpawnEffect();
	void CreateBoomerang();
	void CreateBottomIvy();
	void CreateVine();
	void VineGrowUp();
	void RendererFlash();
	void CollisionCheck();

private:
	inline void GetHit(int _DmgVal)
	{
		SubHp(_DmgVal);
	}

};

