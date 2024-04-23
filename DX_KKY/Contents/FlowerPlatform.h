#pragma once
#include "MoveUnit.h"

// Ό³Έν :
class UCollision;
class USpriteRenderer;
class UDefaultSceneComponent;
class AFlowerPlatform : public UMoveUnit
{
	GENERATED_BODY(UMoveUnit)

public:
	// constrcuter destructer
	AFlowerPlatform();
	~AFlowerPlatform();

	// delete Function
	AFlowerPlatform(const AFlowerPlatform& _Other) = delete;
	AFlowerPlatform(AFlowerPlatform&& _Other) noexcept = delete;
	AFlowerPlatform& operator=(const AFlowerPlatform& _Other) = delete;
	AFlowerPlatform& operator=(AFlowerPlatform&& _Other) noexcept = delete;

protected:

private:
	UCollision* Collider = nullptr;
	USpriteRenderer* Renderer = nullptr;
	UDefaultSceneComponent* Root = nullptr;
	
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
};