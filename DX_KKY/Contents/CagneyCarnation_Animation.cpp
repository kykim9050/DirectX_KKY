#include "PreCompile.h"

#include "CagneyCarnation.h"

void ACagneyCarnation::AnimationInit()
{
	CreateAnimation();
	SetAnimationCallback();

	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetPivot(EPivot::RIGHTBOTTOM);
	Renderer->SetOrder(ERenderingOrder::BossMonster);
}

void ACagneyCarnation::CreateAnimation()
{
	Renderer->CreateAnimation(FlowerBossAniName::Flower_Idle, "FlowerIdle", 0.0416f);
	Renderer->CreateAnimation(FlowerBossAniName::Flower_Intro, "FlowerIntro", 0.0416f, false);

	// Face Attack
	Renderer->CreateAnimation(FlowerBossAniName::Flower_FaceAttackHigh_Begin, "FaceAttackHighBegin", 0.0416f, false);
	Renderer->CreateAnimation(FlowerBossAniName::Flower_FaceAttackHigh_Idle, "FaceAttackHighIdle", 0.067f);
	Renderer->CreateAnimation(FlowerBossAniName::Flower_FaceAttackHigh_End, "FaceAttackHighEnd", 0.067f, false);
	Renderer->CreateAnimation(FlowerBossAniName::Flower_FaceAttackLow_Begin, "FaceAttackLowBegin", 0.0416f, false);
	Renderer->CreateAnimation(FlowerBossAniName::Flower_FaceAttackLow_Idle, "FaceAttackLowIdle", 0.067f);
	Renderer->CreateAnimation(FlowerBossAniName::Flower_FaceAttackLow_End, "FaceAttackLowEnd", 0.067f, false);

}

void ACagneyCarnation::SetAnimationCallback()
{
	// Intro
	Renderer->SetFrameCallback(FlowerBossAniName::Flower_Intro, 38, [this]()
		{
			State.ChangeState(FlowerBossState::Idle);
		});

	// Face Attack High
	Renderer->SetFrameCallback(FlowerBossAniName::Flower_FaceAttackHigh_Begin, 28, [this]()
		{
			State.ChangeState(FlowerBossState::FaceAttackHigh_Idle);
		});
	Renderer->SetFrameCallback(FlowerBossAniName::Flower_FaceAttackHigh_End, 5, [this]()
		{
			State.ChangeState(FlowerBossState::Idle);
		});
	Renderer->SetFrameCallback(FlowerBossAniName::Flower_FaceAttackLow_Begin, 28, [this]()
		{
			State.ChangeState(FlowerBossState::FaceAttackLow_Idle);
		});
	Renderer->SetFrameCallback(FlowerBossAniName::Flower_FaceAttackLow_End, 6, [this]()
		{
			AddActorLocation(FVector(0.0f, 110.f, 0.0f));
			State.ChangeState(FlowerBossState::Idle);
		});


}
