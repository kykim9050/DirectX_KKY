#pragma once
#include "BulletUnit.h"

#define UNPARRYABLE_VALUE 0
#define NOT_DEFINE -1

// Ό³Έν :
class AOctopusBullet : public ABulletUnit
{
	GENERATED_BODY(ABulletUnit)
public:
	// constrcuter destructer
	AOctopusBullet();
	~AOctopusBullet();

	// delete Function
	AOctopusBullet(const AOctopusBullet& _Other) = delete;
	AOctopusBullet(AOctopusBullet&& _Other) noexcept = delete;
	AOctopusBullet& operator=(const AOctopusBullet& _Other) = delete;
	AOctopusBullet& operator=(AOctopusBullet&& _Other) noexcept = delete;

protected:

private:
	int RandomValue = NOT_DEFINE;
	std::string Color = "_None";
	float BulletSpeed = 500.0f;
	float4 ResVelocity = float4::Zero;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void StateInit() override;

	void RendererInit();
	void ColliderInit();
	void AnimationInit();
	void DefineParryableUnit();
	void Fire(float _DeltaTime);
};

