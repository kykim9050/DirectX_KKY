#include "PreCompile.h"
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>

#include "SSBulletFX.h"

ASSBulletFX::ASSBulletFX()
{
}

ASSBulletFX::~ASSBulletFX()
{
}

void ASSBulletFX::BeginPlay()
{
	Super::BeginPlay();

	Renderer->CreateAnimation("SpawnFX", "SSDust", 0.05f, false);
	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetOrder(ERenderingOrder::PlayerBulletFx);
	Renderer->AddPosition(FVector(-150.0f, 0.0f));

	Renderer->SetFrameCallback("SpawnFX", 19, [this]()
		{
			Destroy();
		}
	);


	StateInit();
}

void ASSBulletFX::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}

void ASSBulletFX::StateInit()
{
	Super::StateInit();

	State.CreateState("Spawn");

	State.SetStartFunction("Spawn", [this]()
		{
			Renderer->ChangeAnimation("SpawnFX");
		}
	);

	State.SetUpdateFunction("Spawn", std::bind(&ASSBulletFX::Spawn, this));

	State.ChangeState("Spawn");
}