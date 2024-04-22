#pragma once
#include "BossAttackUnit.h"
#include <EngineCore/StateManager.h>

// Ό³Έν :
class AMiniFlower : public ABossAttackUnit
{
	GENERATED_BODY(ABossAttackUnit)
public:
	// constrcuter destructer
	AMiniFlower();
	~AMiniFlower();

	// delete Function
	AMiniFlower(const AMiniFlower& _Other) = delete;
	AMiniFlower(AMiniFlower&& _Other) noexcept = delete;
	AMiniFlower& operator=(const AMiniFlower& _Other) = delete;
	AMiniFlower& operator=(AMiniFlower&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UStateManager State = UStateManager();
	float4 FlyingDir = float4::Left;
	float UpSpeed = 250.0f;
	float FlyingSpeed = 200.0f;
	float SpitDelay = 4.0f;
	float SpitDelayInit = 4.0f;
	float BulletSpeed = 250.0f;
	std::string PrevState = "None";



	void StateInit() override;
	void RendererInit() override;
	void ColliderInit() override;
	void AnimationInit() override;
	void ResultMovementUpdate(float _DeltaTime) override;

	void Flying(float _DeltaTime);
	void Rising(float _DeltaTime);

	void CreateBullet();

};

