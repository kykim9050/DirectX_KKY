#include "PreCompile.h"
#include "CagneyCarnation.h"

void ACagneyCarnation::StateInit()
{
	State.CreateState(FlowerBossState::Intro);
	State.CreateState(FlowerBossState::Idle);



	State.SetStartFunction(FlowerBossState::Intro, [this]()
		{
			Renderer->ChangeAnimation(FlowerBossAniName::Flower_Intro);
		});
	State.SetStartFunction(FlowerBossState::Idle, [this]()
		{
			Renderer->ChangeAnimation(FlowerBossAniName::Flower_Idle);
		});



	State.SetUpdateFunction(FlowerBossState::Idle, [this](float)
		{

		});
	State.SetUpdateFunction(FlowerBossState::Intro, [this](float)
		{

		});


	State.ChangeState(FlowerBossState::Intro);
}
