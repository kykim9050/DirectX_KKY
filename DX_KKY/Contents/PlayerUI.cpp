#include "PreCompile.h"

#include "PlayerUI.h"
#include "UICalculator.h"

int APlayerUI::PlayerLife = 3;
bool APlayerUI::LifeInfoChange = false;

int APlayerUI::CurSuperMeterIdx = 0;
int APlayerUI::SuperMeterNum = 5;
int APlayerUI::ChargingCount = 0;
int APlayerUI::ChargingMaxCount = 20;
bool APlayerUI::SuperMeterInfoChange = false;
bool APlayerUI::SuperMeterUse = false;
bool APlayerUI::SuperMeterGaugeAdding = false;

APlayerUI::APlayerUI()
{

}

APlayerUI::~APlayerUI()
{

}

void APlayerUI::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerUI::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == SuperMeterGaugeAdding)
	{
		SuperMeterGaugeUpdate();
		SuperMeterGaugeAdding = false;
	}

	if (true == SuperMeterInfoChange)
	{
		SuperMeterUpdate();
		SuperMeterInfoChange = false;
	}

	if (true == LifeInfoChange)
	{
		SubLife();
		LifeInfoChange = false;
	}

	if (true == SuperMeterUse)
	{
		SubSuperMeterCount();
		SuperMeterUse = false;
	}
}

void APlayerUI::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	UIInit();
}

void APlayerUI::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);

	ResetSuperMeterInfo();
}

void APlayerUI::UIInit()
{
	PlayerLife = 3;
	CurSuperMeterIdx = 0;
	ChargingCount = 0;
	SuperMeterInfoChange = false;

	LifeUIInit();
	SuperMetersUIInit();
}

void APlayerUI::SubLife()
{
	if (0 == PlayerLife)
	{
		return;
	}

	LifeUI->ChangeAnimation(GAniName::Player_LifeUI_HP + std::to_string(--PlayerLife));
}

void APlayerUI::LifeUIInit()
{
	LifeUI = CreateWidget<UImage>(GetWorld(), "PlayerLifeUI");
	LifeUI->AddToViewPort(ERenderingOrder::PlayStageUI);
	LifeUI->SetPosition(GRendererPos::LifeUI_Pos);
	LifeUI->SetAutoSize(1.0f, true);

	LifeUI->CreateAnimation(GAniName::Player_LifeUI_HP3, "HP3");
	LifeUI->CreateAnimation(GAniName::Player_LifeUI_HP2, "HP2");
	LifeUI->CreateAnimation(GAniName::Player_LifeUI_HP1, "HP1");
	LifeUI->CreateAnimation(GAniName::Player_LifeUI_HP0, "HP0");
	LifeUI->ChangeAnimation(GAniName::Player_LifeUI_HP3);
}

void APlayerUI::SuperMetersUIInit()
{
	SuperMeters.resize(SuperMeterNum);

	for (int i = 0; i < SuperMeterNum; i++)
	{
		SuperMeters[i] = CreateWidget<UImage>(GetWorld(), "SuperMeter"+std::to_string(i));
		SuperMeters[i]->AddToViewPort(ERenderingOrder::PlayStageUI);
		SuperMeters[i]->SetAutoSize(1.0f, true);
		SuperMeters[i]->SetPosition(float4(-510.0f + 20.0f * i, -310.0f, 0.0f));
		SuperMeters[i]->SetActive(false);
	}
}

void APlayerUI::ResetSuperMeterInfo()
{
	for (int i = 0; i < SuperMeterNum; i++)
	{
		SuperMeters[i]->SetActive(false);
	}

	SuperMeters.clear();
}

void APlayerUI::SuperMeterUpdate()
{
	SuperMeters[CurSuperMeterIdx]->SetActive(true);
	SuperMeters[CurSuperMeterIdx]->SetSprite("SuperMeterCard");
	++CurSuperMeterIdx;

	if (SuperMeterNum == (CurSuperMeterIdx))
	{
		UEngineSound::SoundPlay("sfx_player_parry_power_up_full.wav");
	}
	else
	{
		int RandVal = UMath::RandomReturnInt(1, 2);
		UEngineSound::SoundPlay("sfx_player_parry_power_increment_p" + std::to_string(RandVal) + ".wav");
	}
}

void APlayerUI::SuperMeterCharging()
{
	if (SuperMeterNum <= CurSuperMeterIdx)
	{
		return;
	}

	AddChargingCount();

	if (GetChargingCount() >= GetChargingMaxCount())
	{
		ResetChargingCount();

		SuperMeterInfoChange = true;
	}
	else
	{
		SuperMeterGaugeAdding = true;
	}
}

void APlayerUI::SubSuperMeterCount()
{
	if (0 >= CurSuperMeterIdx)
	{
		return;
	}

	if (5 == CurSuperMeterIdx)
	{
		SuperMeters[--CurSuperMeterIdx]->SetActive(false);
		return;
	}

	SuperMeters[--CurSuperMeterIdx]->SetSprite("SuperMeterCharge", SuperMeterStepInfo);
	SuperMeters[CurSuperMeterIdx + 1]->SetActive(false);
}

void APlayerUI::SuperMeterGaugeUpdate()
{
	SuperMeters[CurSuperMeterIdx]->SetActive(true);

	//for (int i = ChargingMaxCount - 1; i > 0 ; --i)
	//{
	//	if (static_cast<int>(ChargingMaxCount / 5 * i) < ChargingCount)
	//	{
	//		SuperMeters[CurSuperMeterIdx]->SetSprite("SuperMeterCharge", i);
	//		return;
	//	}
	//}
	
	
	if (static_cast<int>(ChargingMaxCount/5 * 4) < ChargingCount)
	{
		SuperMeters[CurSuperMeterIdx]->SetSprite("SuperMeterCharge", 4);
		SuperMeterStepInfo = 4;
		return;
	}
	if (static_cast<int>(ChargingMaxCount / 5 * 3) < ChargingCount)
	{
		SuperMeters[CurSuperMeterIdx]->SetSprite("SuperMeterCharge", 3);
		SuperMeterStepInfo = 3;
		return;
	}
	if (static_cast<int>(ChargingMaxCount / 5 * 2) < ChargingCount)
	{
		SuperMeters[CurSuperMeterIdx]->SetSprite("SuperMeterCharge", 2);
		SuperMeterStepInfo = 2;
		return;
	}
	if (static_cast<int>(ChargingMaxCount / 5 * 1) < ChargingCount)
	{
		SuperMeters[CurSuperMeterIdx]->SetSprite("SuperMeterCharge", 1);
		SuperMeterStepInfo = 1;
		return;
	}
	if (static_cast<int>(ChargingMaxCount / 5 * 0) < ChargingCount)
	{
		SuperMeters[CurSuperMeterIdx]->SetSprite("SuperMeterCharge", 0);
		SuperMeterStepInfo = 0;
		return;
	}
}