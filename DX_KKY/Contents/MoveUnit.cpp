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
	CalJumpVec(_DeltaTime);
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
	
	if (true == BottomCheck(Pos, Color8Bit::Black))
	{
		GravityVec = float4::Zero;
	}
}

void UMoveUnit::SetJumpVec(float4 _JumpVec)
{
	JumpVec = _JumpVec;
}

bool UMoveUnit::BottomCheck(float4 _Pos , Color8Bit _Color)
{
	std::shared_ptr<UEngineTexture> CheckTexture = UContentsValue::ColMapTexture;

	Color8Bit Color = CheckTexture->GetColor(_Pos, _Color);

	if (Color == _Color)
	{
		return true;
	}

	return false;
}

void UMoveUnit::CalJumpVec(float _DeltaTime)
{
	if (true == AvailableAddJumpVec)
	{
		JumpVec += JumpAccVec * _DeltaTime;
	}
}