#include "PreCompile.h"
#include <EngineCore/SpriteRenderer.h>

#include "PlayerBullet.h"
#include "MonsterUnit.h"

APlayerBullet::APlayerBullet()
{
	//SetDamage(1);
	SetDamage(101);
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
	Collision->SetCollisionGroup(ECollisionGroup::PlayerBullet);
	Collision->SetCollisionType(ECollisionType::Rect);

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
	Renderer->CreateAnimation("BulletSpawn", "Peashot_Spawn2", 0.034f, false);

	{
		Renderer->SetFrameCallback("BulletSpawn", 2, [this]()
			{
				State.ChangeState("Flying");
			}
		);
		Renderer->SetFrameCallback("BulletDeath", 6, [this]()
			{
				Destroy();
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
		State.SetUpdateFunction("Spawn", [](float) {});
		State.SetUpdateFunction("Flying", std::bind(&APlayerBullet::Flying, this, std::placeholders::_1));
		State.SetUpdateFunction("Death", [](float) {});
	}

	State.ChangeState("Spawn");
}

void APlayerBullet::Flying(float _DeltaTime)
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

void APlayerBullet::CollisionCheck()
{
	Collision->CollisionEnter(ECollisionGroup::Monster, [=](std::shared_ptr<UCollision> _Collision)
		{
			AMonsterUnit* Monster = dynamic_cast<AMonsterUnit*>(_Collision->GetActor());

			if (nullptr == Monster)
			{
				MsgBoxAssert("충돌 대상이 Monster가 아닙니다.");
				return;
			}

			SetIsMonsterHit(true);

			Monster->SubHp(GetDamage());

			// Player의 SuperMeter 충전해주기

		});
}