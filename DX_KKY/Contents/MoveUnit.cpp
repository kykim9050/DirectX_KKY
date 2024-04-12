#include "PreCompile.h"

#include "MoveUnit.h"

UMoveUnit::UMoveUnit()
{
}

UMoveUnit::~UMoveUnit()
{
}

void UMoveUnit::BeginPlay()
{
	Super::BeginPlay();
}

void UMoveUnit::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void UMoveUnit::ResultMovementUpdate(float _DeltaTime)
{
	//CalHorizonVelocityVector(_DeltaTime);
	//CalGravityVelocityVector(_DeltaTime);
	//CalJumpVelocityVector(_DeltaTime);
	CalMovementVector(_DeltaTime);
	ApplyMovement(_DeltaTime);
}

void UMoveUnit::CalMovementVector(float _DeltaTime)
{
	TotalMovementVec = FVector::Zero;
	TotalMovementVec = TotalMovementVec/* + SpeedVec + GravityVec + JumpVec*/;
}

void UMoveUnit::ApplyMovement(float _DeltaTime)
{
	AddActorLocation(TotalMovementVec * _DeltaTime);

}