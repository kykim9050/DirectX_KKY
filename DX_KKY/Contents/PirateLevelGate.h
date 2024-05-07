#pragma once
#include "GateUnit.h"

// Ό³Έν :
class UDefaultSceneComponent;
class USpriteRenderer;
class UCollision;
class APirateLevelGate : public AGateUnit
{
	GENERATED_BODY(AGateUnit)
public:
	// constrcuter destructer
	APirateLevelGate();
	~APirateLevelGate();

	// delete Function
	APirateLevelGate(const APirateLevelGate& _Other) = delete;
	APirateLevelGate(APirateLevelGate&& _Other) noexcept = delete;
	APirateLevelGate& operator=(const APirateLevelGate& _Other) = delete;
	APirateLevelGate& operator=(APirateLevelGate&& _Other) noexcept = delete;

protected:

private:
	UDefaultSceneComponent* Root = nullptr;
	USpriteRenderer* ShipRenderer = nullptr;
	USpriteRenderer* RipplesRenderer = nullptr;
	UCollision* Collider = nullptr;

private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void RendererInit();
	void ColliderInit();
};

