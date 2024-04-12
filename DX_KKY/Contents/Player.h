#pragma once
#include "MoveUnit.h"

// Ό³Έν :
class UStateManager;
class USpriteRenderer;
class APlayer : public UMoveUnit
{
	GENERATED_BODY(UMoveUnit)

public:
	// constrcuter destructer
	APlayer();
	~APlayer();

	// delete Function
	APlayer(const APlayer& _Other) = delete;
	APlayer(APlayer&& _Other) noexcept = delete;
	APlayer& operator=(const APlayer& _Other) = delete;
	APlayer& operator=(APlayer&& _Other) noexcept = delete;

	inline USpriteRenderer* GetRenderer() const
	{
		return Renderer;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* Renderer;
	UStateManager State = UStateManager();
	EActorDir Dir = EActorDir::Right;

	float RunSpeed = 500.0f;

	void StateInit();
	void CreatePlayerAnimation();
	void MakeDebugMSG();

	void IdleLeft(float _DeltaTime);
	void IdleRight(float _DeltaTime);
	void RunLeft(float _DeltaTime);
	void RunRight(float _DeltaTime);
	void JumpLeft(float _DeltaTime);
	void JumpRight(float _DeltaTime);
		
	inline float GetRunSpeed() const
	{
		return RunSpeed;
	}
};

