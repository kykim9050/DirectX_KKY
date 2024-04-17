#pragma once
#include "FXUnit.h"

// Ό³Έν :
class ABulletFX : public AFXUnit
{
	GENERATED_BODY(AFXUnit)

public:
	// constrcuter destructer
	ABulletFX();
	~ABulletFX();

	// delete Function
	ABulletFX(const ABulletFX& _Other) = delete;
	ABulletFX(ABulletFX&& _Other) noexcept = delete;
	ABulletFX& operator=(const ABulletFX& _Other) = delete;
	ABulletFX& operator=(ABulletFX&& _Other) noexcept = delete;

protected:

private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void StateInit() override;

	void Spawn() {};
};

