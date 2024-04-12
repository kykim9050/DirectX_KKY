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

private:
	float4 TotalMovementVec = float4::Zero;
};
