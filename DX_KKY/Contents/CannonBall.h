#pragma once
#include "BulletUnit.h"

// Ό³Έν :
class ACannonBall : public ABulletUnit
{
	GENERATED_BODY(ABulletUnit)
public:
	// constrcuter destructer
	ACannonBall();
	~ACannonBall();

	// delete Function
	ACannonBall(const ACannonBall& _Other) = delete;
	ACannonBall(ACannonBall&& _Other) noexcept = delete;
	ACannonBall& operator=(const ACannonBall& _Other) = delete;
	ACannonBall& operator=(ACannonBall&& _Other) noexcept = delete;

protected:

private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void StateInit() override;

	void RendererInit();
	void ColliderInit();
	void AnimationInit();

	void Fire(float _DeltaTime);
};

