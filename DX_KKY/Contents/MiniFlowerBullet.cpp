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
	State.CreateState("Fire");

	State.SetStartFunction("Fire", [this]()
		{
			Renderer->ChangeAnimation(FlowerBossAniName::MiniFlower_Bullet);
		});

	State.SetUpdateFunction("Fire", std::bind(&AMiniFlowerBullet::Fire, this, std::placeholders::_1));

	State.ChangeState("Fire");
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

void AMiniFlowerBullet::Fire(float _DeltaTile)
{

}