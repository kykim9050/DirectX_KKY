#include "PreCompile.h"
#include "CagneyCarnation.h"

void ACagneyCarnation::StateInit()
{
	State.CreateState("Idle");

	State.SetStartFunction("Idle", [this]()
		{
			Renderer->ChangeAnimation("Flower_Idle");
		});

	State.SetUpdateFunction("Idle", [this](float)
		{

		});

	State.ChangeState("Idle");
}