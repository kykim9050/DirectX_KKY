#include "PreCompile.h"
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>

#include "BulletFX.h"

ABulletFX::ABulletFX()
{

}

ABulletFX::~ABulletFX()
{
}

void ABulletFX::BeginPlay()
{
	Super::BeginPlay();

	Renderer->CreateAnimation("SpawnFX", "Peashot_Spawn", 0.034f, false);
	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetOrder(ERenderingOrder::PlayerBulletFx);
	Renderer->SetFrameCallback("SpawnFX", 4, [this]()
		{
			Destroy();
		}
	);

	StateInit();
}

void ABulletFX::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}

void ABulletFX::StateInit()
{
	Super::StateInit();

	State.CreateState("Spawn");

	State.SetStartFunction("Spawn", [this]()
		{
			Renderer->ChangeAnimation("SpawnFX");
		}
	);

	State.SetUpdateFunction("Spawn", std::bind(&ABulletFX::Spawn, this));

	State.ChangeState("Spawn");
}