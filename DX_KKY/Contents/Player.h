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
	float JumpVal = 1000.0f;

	void StateInit();
	void CreatePlayerAnimation();
	void MakeDebugMSG();
	void DirCheck();

	void IdleLeft(float _DeltaTime);
	void IdleRight(float _DeltaTime);
	void RunLeft(float _DeltaTime);
	void RunRight(float _DeltaTime);
	void JumpLeft(float _DeltaTime);
	void JumpRight(float _DeltaTime);
	void DuckIdleLeft(float _DeltaTime);
	void DuckIdleRight(float _DeltaTime);
	void DuckLeft(float _DeltaTime);
	void DuckRight(float _DeltaTime);
	void Parry(float _DeltaTime);
		
	std::string ChangeAnimationName(const std::string& _MainName);

	inline float GetRunSpeed() const
	{
		return RunSpeed;
	}

	inline float GetJumpVal() const
	{
		return JumpVal;
	}
};

