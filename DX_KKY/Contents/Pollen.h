#pragma once
#include "BulletUnit.h"

#define PARRYABLE_VALUE 0
#define NOT_DEFINE -1

// Ό³Έν :
class APollen : public ABulletUnit
{
	GENERATED_BODY(ABulletUnit)
public:
	// constrcuter destructer
	APollen();
	~APollen();

	// delete Function
	APollen(const APollen& _Other) = delete;
	APollen(APollen&& _Other) noexcept = delete;
	APollen& operator=(const APollen& _Other) = delete;
	APollen& operator=(APollen&& _Other) noexcept = delete;

protected:

private:
	int RandomValue = NOT_DEFINE;
	std::string Color = "_None";
	float AccTime = 0.0f;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void StateInit() override;

	void RendererInit();
	void ColliderInit();
	void AnimationInit();

	void DefineParryableUnit();
	void Throwing(float _DeltaTime);

};

