#include "PreCompile.h"

#include "UICalculator.h"
#include "PlayerUI.h"

UUICalculator::UUICalculator()
{
}

UUICalculator::~UUICalculator()
{
}

void UUICalculator::SuperMeterChargingCheck()
{
	if (APlayerUI::GetChargingCount() >= APlayerUI::GetChargingMaxCount())
	{
		APlayerUI::ResetChargingCount();

		APlayerUI::SuperMeterChargeEnd();
	}
}

void UUICalculator::SuperMeterCharging()
{
	APlayerUI::AddChargingCount();

	SuperMeterChargingCheck();
}