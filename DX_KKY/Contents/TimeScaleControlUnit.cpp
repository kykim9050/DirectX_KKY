#include "PreCompile.h"

#include "TimeScaleControlUnit.h"

std::shared_ptr<UTimeScaleControlUnit> UTimeScaleControlUnit::TimeController = std::shared_ptr<UTimeScaleControlUnit>();

UTimeScaleControlUnit::UTimeScaleControlUnit()
{
}

UTimeScaleControlUnit::~UTimeScaleControlUnit()
{
}

void UTimeScaleControlUnit::BeginPlay()
{
	Super::BeginPlay();

	SetTimeController(shared_from_this());
}

void UTimeScaleControlUnit::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
