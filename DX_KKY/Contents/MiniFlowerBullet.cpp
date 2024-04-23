#include "PreCompile.h"

#include "MiniFlowerBullet.h"

AMiniFlowerBullet::AMiniFlowerBullet()
{
}

AMiniFlowerBullet::~AMiniFlowerBullet()
{
}

void AMiniFlowerBullet::BeginPlay()
{
	Super::BeginPlay();

	AnimationInit();
	RendererInit();
	ColliderInit();
	StateInit();
}

void AMiniFlowerBullet::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AMiniFlowerBullet::StateInit()
{
	State.CreateState("Init");
	State.CreateState("Fire");

	State.SetStartFunction("Init", [this](){});
	State.SetStartFunction("Fire", [this]()
		{
			float4 PlayerPos = UContentsFunction::GetStagePlayer()->GetActorLocation();
			float4 BulletPos = GetActorLocation();
			float4 TargetDir = (PlayerPos - BulletPos).Normalize2DReturn();

			ResVelocity = TargetDir * BulletSpeed;

			float Theta = UMath::GetInst().DirectionToDeg(TargetDir);
			SetActorRotation(float4(0.0f, 0.0f, Theta));

			Renderer->ChangeAnimation(FlowerBossAniName::MiniFlower_Bullet);
		});

	State.SetUpdateFunction("Init", [this](float) 
		{
			State.ChangeState("Fire");
		});
	State.SetUpdateFunction("Fire", std::bind(&AMiniFlowerBullet::Fire, this, std::placeholders::_1));

	State.ChangeState("Init");
}

void AMiniFlowerBullet::RendererInit()
{
	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetOrder(ERenderingOrder::MonsterBullet);
}

void AMiniFlowerBullet::ColliderInit()
{
	Collision->SetScale(float4(16.0f, 16.0f, 1.0f));
	Collision->SetCollisionGroup(ECollisionGroup::MonsterBullet);
	Collision->SetCollisionType(ECollisionType::Rect);
}

void AMiniFlowerBullet::AnimationInit()
{
	Renderer->CreateAnimation(FlowerBossAniName::MiniFlower_Bullet, "MiniFlowerBullet", 0.0416f);
	Renderer->CreateAnimation(FlowerBossAniName::MiniFlower_BulletDeath, "MiniFlowerBulletDeath", 0.0416f, false);

	Renderer->SetFrameCallback(FlowerBossAniName::MiniFlower_BulletDeath, 5, [this]()
		{
			Destroy();
		});
}

void AMiniFlowerBullet::Fire(float _DeltaTime)
{
	AddActorLocation(ResVelocity * _DeltaTime);
	//ResultMovementUpdate(_DeltaTime);
}
