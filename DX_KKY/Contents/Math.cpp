#include "PreCompile.h"

#include "Math.h"

UMath::UMath()
{
}

UMath::~UMath()
{
}

float UMath::DirectionToDeg(const float4& _Direction)
{
	return DirectionToRad(_Direction) * UEngineMath::RToD;
}

float UMath::DirectionToRad(const float4& _Direction)
{
	float Angle = std::atan(_Direction.Y / _Direction.X);

	if (_Direction.X < 0)
	{
		Angle += PI;
	}

	return Angle;
}
