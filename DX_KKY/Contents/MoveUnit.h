#pragma once
#include <EngineCore/Actor.h>

// 설명 :
class UMoveUnit : public AActor
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	UMoveUnit();
	~UMoveUnit();

	// delete Function
	UMoveUnit(const UMoveUnit& _Other) = delete;
	UMoveUnit(UMoveUnit&& _Other) noexcept = delete;
	UMoveUnit& operator=(const UMoveUnit& _Other) = delete;
	UMoveUnit& operator=(UMoveUnit&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void CalMovementVector(float _DeltaTime);
	void ResultMovementUpdate(float _DeltaTime);
	void ApplyMovement(float _DeltaTime);
	void CalGravityVec(float _DeltaTime);
	bool BottomCheck(float4 _Pos, Color8Bit _Color);
	void CalJumpVec(float _DeltaTime);

	/// <summary>
	/// **주의** Deltatime 곱한 값을 넣지 말 것
	/// 해당 함수는 속도(방향 x 속력)가 들어가야 함
	/// </summary>
	inline void SetSpeedVec(float4 _SpeedVec)
	{
		SpeedVec = _SpeedVec;
	}
	inline void SetJumpVec(float4 _JumpVec)
	{
		JumpVec = _JumpVec;
	}

	inline void SetAvailableAddJumpVec(bool _Value)
	{
		AvailableAddJumpVec = _Value;
	}
	inline float4 GetJumpVec() const
	{
		return JumpVec;
	}
	inline void SetPrevJumpVec(float4 _PrevJumpVec)
	{
		PrevJumpVec = _PrevJumpVec;
	}
	inline float4 GetPrevJumpVec() const
	{
		return PrevJumpVec;
	}

	inline float4 MoveDir(EActorDir _Dir)
	{
		float4 ResVal = float4::Zero;

		switch (_Dir)
		{
		case EActorDir::Left:
		{
			ResVal = float4::Left;
			break;
		}
		case EActorDir::Right:
		{
			ResVal = float4::Right;
			break;
		}
		default:
			break;
		}

		return ResVal;
	}

private:
	float4 TotalMovementVec = float4::Zero;
	float4 SpeedVec = float4::Zero;
	float4 GravityVec = float4::Zero;
	float4 GravityAccVec = float4::Down * 3500.0f;
	float4 JumpVec = float4::Zero;
	float4 JumpAccVec = float4::Up * 3500.0f;
	float4 PrevJumpVec = float4::Zero;

	bool AvailableAddJumpVec = false;
};

