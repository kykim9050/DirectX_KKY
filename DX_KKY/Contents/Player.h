#pragma once
#include "MoveUnit.h"

// 설명 :
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
	float JumpVal = 800.0f;
	float DashSpeed = 800.0f;
	std::string PrevState = "None";

	bool AvailableParry = true;

	void StateInit();
	void CreatePlayerAnimation();
	void MakeDebugMSG();
	/// <summary>
	/// 방향이 다르면 false, 같으면 true
	/// </summary>
	bool DirCheck();

	void Idle(float _DeltaTime);
	void Run(float _DeltaTime);
	void Jump(float _DeltaTime);
	void DuckIdle(float _DeltaTime);
	void Duck(float _DeltaTime);
	void Parry(float _DeltaTime);
	void AfterParry(float _DeltaTime);
	void Dash(float _DeltaTime);
	void DashAir(float _DeltaTime);
	void AfterDashAir(float _DeltaTime);
	void Aim_Up(float _DeltaTime);
	void Aim_DiagonalUp(float _DeltaTime);
	void Aim_Straight(float _DeltaTime);
	void Aim_DiagonalDown(float _DeltaTime);
	void Aim_Down(float _DeltaTime);

	void IdleShoot_Up(float _DeltaTime);
	void IdleShoot_DiagonalUp(float _DeltaTime);
	void IdleShoot_Straight(float _DeltaTime);
	void IdleShoot_DiagonalDown(float _DeltaTime);
	void IdleShoot_Down(float _DeltaTime);
	void IdleShoot_Duck(float _DeltaTime);

	void Run_Shoot_DiagonalUp(float _DeltaTime);
	void Run_Shoot_Straight(float _DeltaTime);

	std::string ChangeStringName(const std::string& _MainName);
	void AnimationDirSet(USpriteRenderer* _Renderer, EActorDir _Dir);

	inline float GetRunSpeed() const
	{
		return RunSpeed;
	}

	inline float GetJumpVal() const
	{
		return JumpVal;
	}
	
	inline bool GetAvailableParry() const
	{
		return AvailableParry;
	}

	inline void SetAvailableParry(bool _Value)
	{
		AvailableParry = _Value;
	}
	inline float GetDashSpeed() const
	{
		return DashSpeed;
	}
	inline void SetPrevState(std::string_view _PrevState)
	{
		PrevState = _PrevState;
	}
	inline std::string GetPrevState() const
	{
		return PrevState;
	}
};

