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
		State.SetStartFunction("Flying", [this]()
			{
				Renderer->ChangeAnimation("BulletFlying");
			}
		);
	}

	{
		State.SetUpdateFunction("Flying", std::bind(&APlayerBullet::Flying, this, std::placeholders::_1));
	}

	State.ChangeState("Flying");
}

void APlayerBullet::Flying(float _DeltaTime)
{

}