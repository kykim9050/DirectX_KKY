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
	float BulletSpeed = 1000.0f;
	bool IsMonsterHit = false;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void StateInit() override;

	void CreateAnimation();

	void Flying(float _DeltaTime);
	void Death(float _DeltaTime);

	void CollisionCheck();


	inline bool GetIsMonsterHit() const
	{
		return IsMonsterHit;
	}
	inline void SetIsMonsterHit(bool _Value)
	{
		IsMonsterHit = _Value;
	}
};

