#pragma once
#include "BossAttackUnit.h"

// Ό³Έν :
class UStateManager;
class USpriteRenderer;
class ASeed : public ABossAttackUnit
{
	GENERATED_BODY(ABossAttackUnit)
public:
	// constrcuter destructer
	ASeed();
	~ASeed();

	// delete Function
	ASeed(const ASeed& _Other) = delete;
	ASeed(ASeed&& _Other) noexcept = delete;
	ASeed& operator=(const ASeed& _Other) = delete;
	ASeed& operator=(ASeed&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UStateManager State = UStateManager();
	USpriteRenderer* VineRenderer = nullptr;

	void ColliderInit();
	void CreateSeedAnimation();
	
	void StateInit();
	void Fall(float _DeltaTime);
	void Plant(float _DeltaTime);
	void GrowUp(float _DeltaTime);

};

