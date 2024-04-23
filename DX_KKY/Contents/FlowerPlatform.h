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
	UDefaultSceneComponent* Root = nullptr;
	UCollision* Collider = nullptr;
	USpriteRenderer* PlatformRenderer = nullptr;
	USpriteRenderer* ShadowRenderer = nullptr;
	USpriteRenderer* PropellorRenderer = nullptr;
	
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void RendererInit();
	void ColliderInit();
	void AnimationInit();

};