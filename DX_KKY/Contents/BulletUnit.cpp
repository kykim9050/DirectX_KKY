#include "PreCompile.h"
#include <EngineCore/DefaultSceneComponent.h>

#include "BulletUnit.h"

ABulletUnit::ABulletUnit()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("BulletRoot");
	SetRoot(Root);

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);
	
	Collision = CreateDefaultSubObject<UCollision>("Collision");
	Collision->SetupAttachment(Root);

}

ABulletUnit::~ABulletUnit()
{
}

void ABulletUnit::BeginPlay()
{
	Super::BeginPlay();

	BoundaryValue = GEngine->EngineWindow.GetWindowScale();
}

void ABulletUnit::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}

bool ABulletUnit::BoundaryCheck(float4 _Boundary, float OffsetX /*= 0.0f*/, float OffsetY /*= 0.0f*/)
{
	float4 MyPos = GetActorLocation();
	MyPos.Y *= -1;

	if (MyPos.X < 50.0f - OffsetX)
	{
		return true;
	}

	if (MyPos.Y < 0.0f - OffsetY)
	{
		return true;
	}

	if (MyPos.X > _Boundary.X - 50.0f + OffsetX)
	{
		return true;
	}

	if (MyPos.Y > _Boundary.Y - 100.0f + OffsetY)
	{
		return true;
	}

	return false;
}