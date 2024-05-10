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

void APlayerUI::UIInit()
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

void APlayerUI::SubLife()
{
	if (0 == PlayerLife)
	{
		return;
	}

	LifeUI->ChangeAnimation(GAniName::Player_LifeUI_HP + std::to_string(--PlayerLife));
}