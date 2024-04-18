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

	//CreateAnimation();

	//Renderer->SetAutoSize(1.0f, true);
	//Renderer->SetOrder(ERenderingOrder::PlayerBullet);

	//Collision->SetScale(UContentsValue::PlayerBulletColSize);
	//Collision->SetCollisionGroup(ECollisionOrder::PlayerBullet);
	//Collision->SetCollisionType(ECollisionType::RotRect);

	StateInit();
}

void APlayerSSBullet::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
