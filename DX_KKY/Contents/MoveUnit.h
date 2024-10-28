#pragma once
#include <EngineCore/Actor.h>

// ���� :
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

	/// <summary>
	/// **����** Deltatime ���� ���� ���� �� ��
	/// �ش� �Լ��� �ӵ�(���� x �ӷ�)�� ���� ��
	/// </summary>
	void SetSpeedVec(float4 _SpeedVec);
	void SetJumpVec(float4 _SpeedVec);

private:
	float4 TotalMovementVec = float4::Zero;
	float4 SpeedVec = float4::Zero;
	float4 GravityVec = float4::Zero;
	float4 GravityAccVec = float4::Down * 2000.0f;
	float4 JumpVec = float4::Zero;
};

