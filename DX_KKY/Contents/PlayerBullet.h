#pragma once
#include "BulletUnit.h"

// Ό³Έν :
class APlayerBullet : public ABulletUnit
{
	GENERATED_BODY(ABulletUnit)

public:
	// constrcuter destructer
	APlayerBullet();
	~APlayerBullet();

	// delete Function
	APlayerBullet(const APlayerBullet& _Other) = delete;
	APlayerBullet(APlayerBullet&& _Other) noexcept = delete;
	APlayerBullet& operator=(const APlayerBullet& _Other) = delete;
	APlayerBullet& operator=(APlayerBullet&& _Other) noexcept = delete;

protected:

private:
	float BulletSpeed = 1600.0f;
	bool IsMonsterHit = false;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void StateInit() override;

	void CreateAnimation();

	void Spawn(float _DeltaTime);
	void Flying(float _DeltaTime);
	void Death(float _DeltaTime);

	void ResultMovementUpdate(float _DeltaTime) override;

	inline bool GetIsMonsterHit() const
	{
		return IsMonsterHit;
	}
	inline void SetIsMonsterHit(bool _Value)
	{
		IsMonsterHit = _Value;
	}

	void CollisionCheck();

};

