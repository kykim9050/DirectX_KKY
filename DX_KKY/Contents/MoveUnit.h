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

	/// <summary>
	/// **주의** Deltatime 곱한 값을 넣지 말 것
	/// 해당 함수는 속도(방향 x 속력)가 들어가야 함
	/// </summary>
	void SetSpeedVec(float4 _Speed);


private:
	float4 TotalMovementVec = float4::Zero;
	float4 SpeedVec = float4::Zero;
};

