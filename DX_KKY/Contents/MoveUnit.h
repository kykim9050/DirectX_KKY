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

	virtual void ResultMovementUpdate(float _DeltaTime);
	virtual void CalGravityVec(float _DeltaTime);
	virtual void CalJumpVec(float _DeltaTime);
	void CalMovementVector(float _DeltaTime);
	void ApplyMovement(float _DeltaTime);
	bool PixelCheck(float4 _Pos, Color8Bit _Color);
	void AddGravityVec(float _Ratio, float _DeltaTime);

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
	inline void SetGravityVec(float4 _GravityVec)
	{
		GravityVec = _GravityVec;
	}
	inline void SetGravityAccVec(float4 _GravityAccVec)
	{
		GravityAccVec = _GravityAccVec;
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
	inline float4 GetGravityVec() const
	{
		return GravityVec;
	}
	inline void SetPrevGravityVec(float4 _PrevGravityVec)
	{
		PrevGravityVec = _PrevGravityVec;
	}
	inline float4 GetPrevGravityVec() const
	{
		return PrevGravityVec;
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
	float4 GravityAccVec = float4::Down * 4000.0f;
	float4 JumpVec = float4::Zero;
	float4 JumpAccVec = float4::Up * 4000.0f;
	float4 PrevJumpVec = float4::Zero;
	float4 PrevGravityVec = float4::Zero;

	bool AvailableAddJumpVec = false;
};

