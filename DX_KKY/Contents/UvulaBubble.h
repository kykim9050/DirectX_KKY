#pragma once
#include "BulletUnit.h"

// Ό³Έν :
class AUvulaBubble : public ABulletUnit
{
	GENERATED_BODY(ABulletUnit)
public:
	// constrcuter destructer
	AUvulaBubble();
	~AUvulaBubble();

	// delete Function
	AUvulaBubble(const AUvulaBubble& _Other) = delete;
	AUvulaBubble(AUvulaBubble&& _Other) noexcept = delete;
	AUvulaBubble& operator=(const AUvulaBubble& _Other) = delete;
	AUvulaBubble& operator=(AUvulaBubble&& _Other) noexcept = delete;

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

