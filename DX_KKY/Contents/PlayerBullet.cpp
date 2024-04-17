#include "PreCompile.h"
#include <EngineCore/SpriteRenderer.h>

#include "PlayerBullet.h"


APlayerBullet::APlayerBullet()
{
	SetHorizontalSpeed(1000.0f);
	SetVerticalSpeed(1000.0f);
}

APlayerBullet::~APlayerBullet()
{
}

void APlayerBullet::BeginPlay()
{
	Super::BeginPlay();

	CreateAnimation();

	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetOrder(ERenderingOrder::PlayerBullet);

	Collision->SetScale(UContentsValue::PlayerBulletColSize);
	Collision->SetCollisionGroup(ECollisionOrder::PlayerBullet);
	Collision->SetCollisionType(ECollisionType::Rect);

	StateInit();
}

void APlayerBullet::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}

void APlayerBullet::CreateAnimation()
{
	Renderer->CreateAnimation("BulletDeath", "Peashot_Death", 0.034f, false);
	Renderer->CreateAnimation("BulletFlying", "Peashot_Loop", 0.034f);
	Renderer->CreateAnimation("BulletSpawn", "Peashot_Spawn2", 0.034f, false);

	{
		Renderer->SetFrameCallback("BulletSpawn", 2, [this]()
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
		State.CreateState("Spawn");
		State.CreateState("Flying");
		State.CreateState("Death");
	}

	{
		State.SetStartFunction("Spawn", [this]()
			{
				Renderer->ChangeAnimation("BulletSpawn");
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
		State.SetUpdateFunction("Spawn", std::bind(&APlayerBullet::Spawn, this, std::placeholders::_1));
		State.SetUpdateFunction("Flying", std::bind(&APlayerBullet::Flying, this, std::placeholders::_1));
		State.SetUpdateFunction("Death", std::bind(&APlayerBullet::Death, this, std::placeholders::_1));
	}

	State.ChangeState("Spawn");
}

void APlayerBullet::Flying(float _DeltaTime)
{
	SetSpeedVec(GetHorizontalDir() * BulletSpeed);
	SetJumpVec(GetVerticalDir() * BulletSpeed);
	ResultMovementUpdate(_DeltaTime);
}

void APlayerBullet::Spawn(float _DeltaTime)
{
	SetSpeedVec(GetHorizontalDir() * BulletSpeed);
	SetJumpVec(GetVerticalDir() * BulletSpeed);
	ResultMovementUpdate(_DeltaTime);
}

void APlayerBullet::Death(float _DeltaTime)
{

}

void APlayerBullet::ResultMovementUpdate(float _DeltaTime)
{
	Super::ResultMovementUpdate(_DeltaTime);
}