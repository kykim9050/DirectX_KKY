#pragma once
#include "FXUnit.h"

// Ό³Έν :
class ASSBulletFX : public AFXUnit
{
	GENERATED_BODY(AFXUnit)
public:
	// constrcuter destructer
	ASSBulletFX();
	~ASSBulletFX();

	// delete Function
	ASSBulletFX(const ASSBulletFX& _Other) = delete;
	ASSBulletFX(ASSBulletFX&& _Other) noexcept = delete;
	ASSBulletFX& operator=(const ASSBulletFX& _Other) = delete;
	ASSBulletFX& operator=(ASSBulletFX&& _Other) noexcept = delete;

protected:

private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void StateInit() override;

	void Spawn() {};
};

