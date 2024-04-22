#include "PreCompile.h"

#include "PlayerSSBullet.h"
#include "MonsterUnit.h"

APlayerSSBullet::APlayerSSBullet()
{
	SetDamage(5);
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
				DelayCallBack(2.0f, [this]()
					{
						Destroy();
					});
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
		Renderer->SetFrameCallback("BulletDeath", 10, [this]()
			{
				Destroy();
			}
		);
	}
}

void APlayerSSBullet::Flying(float _DeltaTime)
{
	CollisionCheck();

	if (true == GetIsMonsterHit())
	{
		State.ChangeState("Death");
		return;
	}

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

void APlayerSSBullet::CollisionCheck()
{
	Collision->CollisionEnter(ECollisionGroup::Monster, [=](std::shared_ptr<UCollision> _Collision)
		{
			UMonsterUnit* Monster = dynamic_cast<UMonsterUnit*>(_Collision->GetActor());

			if (nullptr == Monster)
			{
				MsgBoxAssert("충돌 대상이 Monster가 아닙니다.");
				return;
			}

			SetIsMonsterHit(true);

			Monster->GetHit(GetDamage());

			// Player의 SuperMeter 충전해주기

		});
}