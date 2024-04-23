#pragma once
#include "BulletUnit.h"

// Ό³Έν :
class AMiniFlowerBullet : public ABulletUnit
{
	GENERATED_BODY(ABulletUnit)

public:
	// constrcuter destructer
	AMiniFlowerBullet();
	~AMiniFlowerBullet();

	// delete Function
	AMiniFlowerBullet(const AMiniFlowerBullet& _Other) = delete;
	AMiniFlowerBullet(AMiniFlowerBullet&& _Other) noexcept = delete;
	AMiniFlowerBullet& operator=(const AMiniFlowerBullet& _Other) = delete;
	AMiniFlowerBullet& operator=(AMiniFlowerBullet&& _Other) noexcept = delete;

	inline void SetBulletLocation(float4 _Pos)
	{
		SetActorLocation(_Pos);
	}

protected:

private:
	float4 Velocity = FVector::Zero;
	float BulletSpeed = 250.0f;
	float4 ResVelocity = float4::Zero;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void StateInit() override;

	void RendererInit();
	void ColliderInit();
	void AnimationInit();

	void Fire(float _DeltaTime);
};

