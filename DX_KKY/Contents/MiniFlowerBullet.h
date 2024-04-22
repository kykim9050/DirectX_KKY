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

protected:

private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void StateInit() override;

	void RendererInit();
	void ColliderInit();
	void AnimationInit();
};

