#include "PreCompile.h"

#include "CagneyCarnation.h"

void ACagneyCarnation::AnimationInit()
{
	CreateAnimation();
	SetAnimationCallback();

	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetPivot(EPivot::RIGHT);
	Renderer->SetOrder(ERenderingOrder::BossMonster);
}

void ACagneyCarnation::CreateAnimation()
{
	Renderer->CreateAnimation(FlowerBossAniName::Flower_Idle, "FlowerIdle", 0.0416f);
	Renderer->CreateAnimation(FlowerBossAniName::Flower_Intro, "FlowerIntro", 0.0416f, false);
}

void ACagneyCarnation::SetAnimationCallback()
{
	Renderer->SetFrameCallback(FlowerBossAniName::Flower_Intro, 38, [this]()
		{
			State.ChangeState(FlowerBossState::Idle);
		});
}
