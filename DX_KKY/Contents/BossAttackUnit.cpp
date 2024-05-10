#include "PreCompile.h"
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/Collision.h>
#include <EngineCore/SpriteRenderer.h>

#include "BossAttackUnit.h"


ABossAttackUnit::ABossAttackUnit()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("BossAttRoot");
	SetRoot(Root);
	
	Renderer = CreateDefaultSubObject<USpriteRenderer>("BossAttRenderer");
	Renderer->SetupAttachment(Root);

	Collider = CreateDefaultSubObject<UCollision>("BossAttCollider");
	Collider->SetupAttachment(Root);
}

ABossAttackUnit::~ABossAttackUnit()
{
}

void ABossAttackUnit::BeginPlay()
{
	Super::BeginPlay();
}

void ABossAttackUnit::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}


void ABossAttackUnit::SetRendererPivot(EPivot _Pivot)
{
	switch (_Pivot)
	{
	case EPivot::RIGHT:
	case EPivot::BOT:
	case EPivot::LEFTTOP:
	case EPivot::RIGHTBOTTOM:
		break;
	default:
		MsgBoxAssert("이미지에 유효하지 않은 Pivot 정보를 적용하려 했습니다.");
		break;
	}

	Renderer->SetPivot(_Pivot);
}



void ABossAttackUnit::CreateAnimation(FAniInfo _Info, bool _Loop)
{
	Renderer->CreateAnimation(_Info.AnimationName, _Info.SpriteName, _Info.InterTime, _Loop);
}

void ABossAttackUnit::ChangeAnimation(std::string_view _AnimationName)
{
	Renderer->ChangeAnimation(_AnimationName);
}

void ABossAttackUnit::CreateRevAnimation(FAniInfo _Info, bool _Loop, int _Start, int _End)
{
	Renderer->CreateAnimation(_Info.AnimationName, _Info.SpriteName, _Info.InterTime, _Loop, _Start, _End);
}

bool ABossAttackUnit::BoundaryCheck(float4 _Boundary, float OffsetX /*= 0.0f*/, float OffsetY /*= 0.0f*/)
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