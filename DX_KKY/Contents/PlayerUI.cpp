#include "PreCompile.h"

#include "PlayerUI.h"

int APlayerUI::PlayerLife = 3;
UImage* APlayerUI::LifeUI = nullptr;

APlayerUI::APlayerUI()
{

}

APlayerUI::~APlayerUI()
{

}

void APlayerUI::BeginPlay()
{
	Super::BeginPlay();

	UIInit();
}

void APlayerUI::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void APlayerUI::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);

	SuperMeters.clear();
}

void APlayerUI::UIInit()
{
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
		SuperMeters[i]->SetSprite("SuperMeterCard");
	}
}