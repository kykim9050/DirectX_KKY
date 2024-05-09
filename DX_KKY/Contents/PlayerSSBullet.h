#pragma once
#include "BulletUnit.h"

// Ό³Έν :
class APlayerSSBullet : public ABulletUnit
{
	GENERATED_BODY(ABulletUnit)

public:
	// constrcuter destructer
	APlayerSSBullet();
	~APlayerSSBullet();

	// delete Function
	APlayerSSBullet(const APlayerSSBullet& _Other) = delete;
	APlayerSSBullet(APlayerSSBullet&& _Other) noexcept = delete;
	APlayerSSBullet& operator=(const APlayerSSBullet& _Other) = delete;
	APlayerSSBullet& operator=(APlayerSSBullet&& _Other) noexcept = delete;

protected:

private:
	float SpawnDelay = 0.2f;
	float SpawnDelayInit = 0.2f;
	float BulletSpeed = 1300.0f;
	float AfterHitBulletAccSpeed = 8000.0f;
	bool IsMonsterHit = false;
	int HitTime = 3;
	float AfterHitDelay = 0.12f;
	float AfterHitDelayInit = 0.12f;

private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void StateInit() override;

	void CreateAnimation();

	void Init(float _DeltaTime);
	void Flying(float _DeltaTime);
	void Death(float _DeltaTime);
	void Hit(float _DeltaTime);

	void CollisionCheck();
	void PlayHitSound();


	inline bool GetIsMonsterHit() const
	{
		return IsMonsterHit;
	}
	inline void SetIsMonsterHit(bool _Value)
	{
		IsMonsterHit = _Value;
	}
};

