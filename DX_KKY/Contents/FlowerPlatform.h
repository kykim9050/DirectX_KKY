#pragma once
#include "MoveUnit.h"
#include <EngineCore/StateManager.h>


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

	inline void SetPressed()
	{
		State.ChangeState(FlowerBossState::FlowerPlatform_Pressed);
		return;
	}
	inline void PressedOver()
	{
		State.ChangeState(FlowerBossState::FlowerPlatform_Floating);
		return;
	}
	inline bool GetIsPressed()
	{
		if (FlowerBossState::FlowerPlatform_Pressed == State.GetCurStateName())
		{
			return true;
		}
		return false;
	}
	void CreatePlatformAnimation(FAniInfo _info, bool _Loop = true);
	void ChangePlatformAnimation(std::string_view _AniName);


protected:

private:
	UDefaultSceneComponent* Root = nullptr;
	UCollision* Collider = nullptr;
	USpriteRenderer* PlatformRenderer = nullptr;
	USpriteRenderer* ShadowRenderer = nullptr;
	USpriteRenderer* PropellorRenderer = nullptr;
	UStateManager State;
	
	float4 FloatingDir = float4::Up;
	float FloatingSpeed = 10.0f;
	float PressedSpeed = 50.0f;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void RendererInit();
	void ColliderInit();
	void AnimationInit();
	void StateInit();

	void Floating(float _DeltaTime);
	void Pressed(float _DeltaTime);

};