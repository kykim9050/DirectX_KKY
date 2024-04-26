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

void UTimeScaleControlUnit::RecoveryTimeScale(std::function<void()> _Function, float _DelayTime)
{

	DelayCallBack(_DelayTime, [_Function]()
		{
			for (int i = 0; i < static_cast<int>(EActorType::Max); i++)
			{
				GEngine->SetOrderTimeScale(i, 1.0f);
			}

			_Function();
		});
}