#pragma once
#include "GateUnit.h"

// Ό³Έν :
class UDefaultSceneComponent;
class USpriteRenderer;
class UCollision;
class AFlowerLevelGate : public AGateUnit
{
	GENERATED_BODY(AGateUnit)
public:
	// constrcuter destructer
	AFlowerLevelGate();
	~AFlowerLevelGate();

	// delete Function
	AFlowerLevelGate(const AFlowerLevelGate& _Other) = delete;
	AFlowerLevelGate(AFlowerLevelGate&& _Other) noexcept = delete;
	AFlowerLevelGate& operator=(const AFlowerLevelGate& _Other) = delete;
	AFlowerLevelGate& operator=(AFlowerLevelGate&& _Other) noexcept = delete;

protected:

private:
	UDefaultSceneComponent* Root = nullptr;
	USpriteRenderer* Renderer = nullptr;
	UCollision* Collider = nullptr;

private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void RendererInit();
	void ColliderInit();
};

