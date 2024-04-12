#include "PreCompile.h"
#include <EngineCore/EngineTexture.h>

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
	CalGravityVec(_DeltaTime);
	//CalJumpVec(_DeltaTime);
	CalMovementVector(_DeltaTime);
	ApplyMovement(_DeltaTime);
}

void UMoveUnit::CalMovementVector(float _DeltaTime)
{
	TotalMovementVec = FVector::Zero;
	TotalMovementVec = TotalMovementVec + SpeedVec + GravityVec + JumpVec  ;
}

void UMoveUnit::ApplyMovement(float _DeltaTime)
{
	AddActorLocation(TotalMovementVec * _DeltaTime);
}

void UMoveUnit::SetSpeedVec(float4 _SpeedVec)
{
	SpeedVec = _SpeedVec;
}


void UMoveUnit::CalGravityVec(float _DeltaTime)
{
	float4 Pos = GetActorLocation();
	Pos.Y = -Pos.Y;

	GravityVec += GravityAccVec * _DeltaTime;

	std::shared_ptr<UEngineTexture> CheckTexture = UContentsValue::ColMapTexture;

	Color8Bit Color = CheckTexture->GetColor(Pos, Color8Bit::Black);

	if (Color == Color8Bit::Black)
	{
		GravityVec = float4::Zero;
	}
}

void UMoveUnit::SetJumpVec(float4 _JumpVec)
{
	JumpVec = _JumpVec;
}