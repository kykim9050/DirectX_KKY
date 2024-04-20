#include "PreCompile.h"

#include "PlayerSSBullet.h"

APlayerSSBullet::APlayerSSBullet()
{
	SetHorizontalSpeed(1000.0f);
	SetVerticalSpeed(1000.0f);
}

APlayerSSBullet::~APlayerSSBullet()
{
}

void APlayerSSBullet::BeginPlay()
{
	Super::BeginPlay();

	CreateAnimation();

	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetOrder(ERenderingOrder::PlayerBullet);

	Collision->SetScale(UContentsValue::PlayerSSBulletColSize);
	Collision->SetCollisionGroup(ECollisionGroup::PlayerBullet);
	Collision->SetCollisionType(ECollisionType::RotRect);
	Collision->AddPosition(FVector(150.0f, 0.0f));

	StateInit();
}

void APlayerSSBullet::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void APlayerSSBullet::StateInit()
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
		State.SetUpdateFunction("Spawn", std::bind(&APlayerSSBullet::Spawn, this, std::placeholders::_1));
		State.SetUpdateFunction("Flying", std::bind(&APlayerSSBullet::Flying, this, std::placeholders::_1));
		State.SetUpdateFunction("Death", std::bind(&APlayerSSBullet::Death, this, std::placeholders::_1));
	}

	State.ChangeState("Spawn");
}

void APlayerSSBullet::CreateAnimation()
{

	Renderer->CreateAnimation("BulletSpawn", "PeaEX_Spawn", 0.0416f, false);
	Renderer->CreateAnimation("BulletFlying", "PeaEX_Loop", 0.034f);
	Renderer->CreateAnimation("BulletDeath", "PeaEX_Death", 0.0416f, false);

	{
		Renderer->SetFrameCallback("BulletSpawn", 3, [this]()
			{
				State.ChangeState("Flying");
			}
		);
	}
}

void APlayerSSBullet::Flying(float _DeltaTime)
{
	SetSpeedVec(GetHorizontalDir() * BulletSpeed);
	SetJumpVec(GetVerticalDir() * BulletSpeed);
	ResultMovementUpdate(_DeltaTime);
}

void APlayerSSBullet::Spawn(float _DeltaTime)
{
	SetSpeedVec(GetHorizontalDir() * BulletSpeed);
	SetJumpVec(GetVerticalDir() * BulletSpeed);
	ResultMovementUpdate(_DeltaTime);
}

void APlayerSSBullet::Death(float _DeltaTime)
{

}

void APlayerSSBullet::ResultMovementUpdate(float _DeltaTime)
{
	Super::ResultMovementUpdate(_DeltaTime);
}