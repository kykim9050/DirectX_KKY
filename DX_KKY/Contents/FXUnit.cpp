#include "PreCompile.h"
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>

#include "FXUnit.h"

AFXUnit::AFXUnit()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("FXRoot");
	SetRoot(Root);

	Renderer = CreateDefaultSubObject<USpriteRenderer>("FXRenderer");
	Renderer->SetupAttachment(Root);
}

AFXUnit::~AFXUnit()
{
}

void AFXUnit::BeginPlay()
{
	Super::BeginPlay();
}

void AFXUnit::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AFXUnit::CreateAnimation(FAniInfo _Info, bool _Loop)
{
	Renderer->CreateAnimation(_Info.AnimationName, _Info.SpriteName, _Info.InterTime, _Loop);
}

void AFXUnit::ChangeAnimation(std::string_view _AnimationName)
{
	Renderer->ChangeAnimation(_AnimationName);
}

void AFXUnit::SetRendererPivot(EPivot _Pivot)
{
	switch (_Pivot)
	{
	case EPivot::RIGHT:
	case EPivot::BOT:
	case EPivot::LEFTTOP:
	case EPivot::RIGHTBOTTOM:
		break;
	default:
		MsgBoxAssert("�̹����� ��ȿ���� ���� Pivot ������ �����Ϸ� �߽��ϴ�.");
		break;
	}

	Renderer->SetPivot(_Pivot);
}