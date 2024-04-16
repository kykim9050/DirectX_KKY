#include "PreCompile.h"
#include <EngineCore/SpriteRenderer.h>

#include "PlayerBullet.h"


APlayerBullet::APlayerBullet()
{
}

APlayerBullet::~APlayerBullet()
{
}

void APlayerBullet::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetOrder(ERenderingOrder::PlayerBullet);

	CreateAnimation();

	StateInit();
}

void APlayerBullet::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void APlayerBullet::CreateAnimation()
{
	Renderer->CreateAnimation("BulletDeath", "Peashot_Death", 0.034f, false);
	Renderer->CreateAnimation("BulletFlying", "Peashot_Loop", 0.034f);
	Renderer->CreateAnimation("BulletSpawn1", "Peashot_Spawn", 0.034f, false);
	Renderer->CreateAnimation("BulletSpawn2", "Peashot_Spawn2", 0.034f, false);

	{
		Renderer->SetFrameCallback("BulletSpawn1", 4, [this]()
			{
				State.ChangeState("Spawn2");
			}
		);

		Renderer->SetFrameCallback("BulletSpawn2", 2, [this]()
			{
				State.ChangeState("Flying");
			}
		);
	}
}

void APlayerBullet::StateInit()
{
	Super::StateInit();

	{
		State.CreateState("Spawn1");
		State.CreateState("Spawn2");
		State.CreateState("Flying");
		State.CreateState("Death");
	}

	{
		State.SetStartFunction("Spawn1", [this]()
			{
				Renderer->ChangeAnimation("BulletSpawn1");
			}
		);
		State.SetStartFunction("Spawn2", [this]()
			{
				Renderer->ChangeAnimation("BulletSpawn2");
			}
		);
		State.SetStartFunction("Flying", [this]()
			{
				Renderer->ChangeAnimation("BulletFlying");
			}
		);
		State.SetStartFunction("Death", [this]()
			{
				Renderer->ChangeAnimation("BulletDeath");
			}
		);
	}

	{
		State.SetUpdateFunction("Flying", std::bind(&APlayerBullet::Flying, this, std::placeholders::_1));
	}

	State.ChangeState("Spawn1");
}

void APlayerBullet::Flying(float _DeltaTime)
{

}