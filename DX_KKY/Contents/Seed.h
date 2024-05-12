#pragma once
#include "BulletUnit.h"

// Ό³Έν :
class UStateManager;
class USpriteRenderer;
class ASeed : public ABulletUnit
{
	GENERATED_BODY(ABulletUnit)
public:
	// constrcuter destructer
	ASeed();
	~ASeed();

	// delete Function
	ASeed(const ASeed& _Other) = delete;
	ASeed(ASeed&& _Other) noexcept = delete;
	ASeed& operator=(const ASeed& _Other) = delete;
	ASeed& operator=(ASeed&& _Other) noexcept = delete;

	void SetColor(ESeedColor _Color);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* VineRenderer = nullptr;


	ESeedColor Color = ESeedColor::None;
	const float SeedFallEndValue = -620.0f;
	const float SeedFallSpeed = 120.0f;
	const float ColliderYOffset = 20.0f;

	void Fall(float _DeltaTime);
	void Plant(float _DeltaTime);
	void GrowUp(float _DeltaTime);

	void CreateChomper();
	void CreateVenus();
	void CreateMiniFlower();

	void StateInit() override;
	void RendererInit() override;
	void ColliderInit() override;
	void AnimationInit() override;
};

