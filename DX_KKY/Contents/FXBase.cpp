#include "PreCompile.h"
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>

#include "FXBase.h"

AFXBase::AFXBase()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("FXRoot");
	SetRoot(Root);

	Renderer = CreateDefaultSubObject<USpriteRenderer>("FXRenderer");
	Renderer->SetupAttachment(Root);
}

AFXBase::~AFXBase()
{
}

void AFXBase::BeginPlay()
{
	Super::BeginPlay();
}

void AFXBase::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	FXDestroyCheck();
}

void AFXBase::FXInit(ERenderingOrder _Order, FAniInfo _Info, bool _Loop)
{
	Loop = _Loop;

	Renderer->CreateAnimation(_Info.AnimationName, _Info.SpriteName, _Info.InterTime, Loop);
	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetOrder(_Order);
	Renderer->ChangeAnimation(_Info.AnimationName);
}

void AFXBase::FXDestroyCheck()
{
	if (Renderer->IsCurAnimationEnd() && false == Loop)
	{
		Destroy();
	}
}

void AFXBase::SetImgDir(EEngineDir _ImgDir)
{
	switch (_ImgDir)
	{
	case EEngineDir::Left:
		Renderer->SetDir(EEngineDir::Left);
		break;
	case EEngineDir::Right:
		Renderer->SetDir(EEngineDir::Right);
		break;
	default:
		MsgBoxAssert("유효하지 않은 방향 값 입니다.");
		break;
	}
}

void AFXBase::FXDestroy()
{
	Destroy();
}

void AFXBase::SetImgPivot(EPivot _Pivot)
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