#include "PreCompile.h"

#include "PlayerSSBullet.h"
#include "MonsterUnit.h"
#include "UICalculator.h"

APlayerSSBullet::APlayerSSBullet()
{
	SetDamage(3);
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
	Renderer->SetActive(false);

	Collision->SetScale(UContentsValue::PlayerSSBulletColSize);
	Collision->SetCollisionGroup(ECollisionGroup::PlayerBullet);
	Collision->SetCollisionType(ECollisionType::RotRect);
	Collision->AddPosition(FVector(150.0f, 0.0f));
	Collision->SetActive(false);

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
		State.CreateState("Init");
		State.CreateState("Spawn");
		State.CreateState("Flying");
		State.CreateState("Hit");
		State.CreateState("Death");
	}

	{
		State.SetStartFunction("Init", []() {});
		State.SetStartFunction("Spawn", [this]()
			{
				Renderer->SetActive(true);
				Renderer->ChangeAnimation("BulletSpawn");

				Collision->SetActive(true);
			}
		);
		State.SetStartFunction("Flying", [this]()
			{
				Renderer->ChangeAnimation("BulletFlying");
				DelayCallBack(2.0f, [this]()
					{
						Destroy();
					});
			}
		);
		State.SetStartFunction("Hit", [this]()
			{
				--HitTime;
				PlayHitSound();
				SetSpeedVec(float4::Zero);
				SetJumpVec(float4::Zero);
				Collision->SetActive(false);
			});
		State.SetStartFunction("Death", [this]()
			{
				PlayHitSound();
				Renderer->ChangeAnimation("BulletDeath");
			}
		);
	}

	{
		State.SetUpdateFunction("Init", std::bind(&APlayerSSBullet::Init, this, std::placeholders::_1));
		State.SetUpdateFunction("Spawn", [](float) {});
		State.SetUpdateFunction("Flying", std::bind(&APlayerSSBullet::Flying, this, std::placeholders::_1));
		State.SetUpdateFunction("Hit", std::bind(&APlayerSSBullet::Hit, this, std::placeholders::_1));
		State.SetUpdateFunction("Death", std::bind(&APlayerSSBullet::Death, this, std::placeholders::_1));
	}

	{
		State.SetEndFunction("Init", [this]()
			{
				SpawnDelay = SpawnDelayInit;
			});
		State.SetEndFunction("Hit", [this]()
			{
				if (0 >= HitTime)
				{
					return;
				}

				Collision->SetActive(true);
			});
	}

	State.ChangeState("Init");
}

void APlayerSSBullet::CreateAnimation()
{

	Renderer->CreateAnimation("BulletSpawn", "PeaEX_Spawn", 0.01f, false);
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
		if (0 < HitTime)
		{
			State.ChangeState("Hit");
			return;
		}

		State.ChangeState("Death");
		return;
	}

	SetSpeedVec(GetHorizontalDir() * BulletSpeed);
	SetJumpVec(GetVerticalDir() * BulletSpeed);
	ResultMovementUpdate(_DeltaTime);
}

void APlayerSSBullet::Death(float _DeltaTime)
{

}

void APlayerSSBullet::CollisionCheck()
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
			Monster->ExcuteGetHitFunction();

			// Player의 SuperMeter 충전해주기
			UUICalculator::SuperMeterCharging();

		});
}

void APlayerSSBullet::Init(float _DeltaTime)
{
	SpawnDelay -= _DeltaTime;

	if (0.0f >= SpawnDelay)
	{
		State.ChangeState("Spawn");
		return;
	}
}

void APlayerSSBullet::Hit(float _DeltaTime)
{
	AfterHitDelay -= _DeltaTime;

	if (0.0f >= AfterHitDelay)
	{
		AfterHitDelay = AfterHitDelayInit + AfterHitDelay;

		State.ChangeState("Flying");
		return;
	}

	AccSpeedVec(GetHorizontalDir() * _DeltaTime, AfterHitBulletAccSpeed);
	AccJumpVec(GetVerticalDir() * _DeltaTime, AfterHitBulletAccSpeed);
	ResultMovementUpdate(_DeltaTime);
}

void APlayerSSBullet::PlayHitSound()
{
	UEngineSound::SoundPlay("sfx_player_weapon_peashoot_ex_impact_01.wav");
}