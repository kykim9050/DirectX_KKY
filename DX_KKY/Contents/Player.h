#pragma once
#include "MoveUnit.h"

// ���� :
class UStateManager;
class APlayerBullet;
class USpriteRenderer;
class APlayer : public UMoveUnit , public std::enable_shared_from_this<APlayer>
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

	inline static std::shared_ptr<APlayer> GetMainPlayer()
	{
		return MainPlayer;
	}

	inline USpriteRenderer* GetRenderer() const
	{
		return Renderer;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void ResultMovementUpdate(float _DeltaTime) override;
	void CalGravityVec(float _DeltaTime) override;
	void CalJumpVec(float _DeltaTime) override;

private:
	static std::shared_ptr<APlayer> MainPlayer;

	USpriteRenderer* Renderer;
	UStateManager State = UStateManager();
	EActorDir Dir = EActorDir::Right;
	EBulletShootType ShootType = EBulletShootType::None;

	float RunSpeed = 500.0f;
	float JumpVal = 900.0f;
	float DashSpeed = 800.0f;
	float ShootDelayTime = 0.25f;
	float ShootDelayInitTime = 0.25f;
	float SSReboundSpeed = 85.0f;
	std::string PrevState = "None";

	bool AvailableParry = true;
	bool AvailableDownJump = false;

	void StateInit();
	void CreatePlayerAnimation();
	void MakeDebugMSG();
	/// <summary>
	/// ������ �ٸ��� false, ������ true
	/// </summary>
	bool DirCheck();
	void WallCheck(float _DeltaTime);
	bool DownJumpCheck();

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
	void DownJump(float _DeltaTime);
	void FallDown(float _DeltaTime);
	
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

	void Ground_SS_Up(float _DeltaTime);
	void Ground_SS_DiagonalUp(float _DeltaTime);
	void Ground_SS_Straight(float _DeltaTime);
	void Ground_SS_DiagonalDown(float _DeltaTime);
	void Ground_SS_Down(float _DeltaTime);

	void ShootBullet(float _DeltaTime);
	void ShootCheck(float _DeltaTime);
	void GetBulletInitPosAndRot(FVector& _Pos, FVector& _Rot, std::shared_ptr<APlayerBullet>& _Bullet);
	void JumpShootInit(FVector& _Pos, FVector& _Rot, std::shared_ptr<APlayerBullet>& _Bullet);

	std::string ChangeStringName(const std::string& _MainName);
	void AnimationDirSet(USpriteRenderer* _Renderer, EActorDir _Dir);


	inline void SetMainPlayer(std::shared_ptr<APlayer> _Player)
	{
		MainPlayer = _Player;
	}
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
	inline void SetShootType(EBulletShootType _ShootType)
	{
		ShootType = _ShootType;
	}
	inline void SetAvailableDownJump(bool _Value)
	{
		AvailableDownJump = _Value;
	}
	inline bool GetAvailableDownJump() const
	{
		return AvailableDownJump;
	}
};