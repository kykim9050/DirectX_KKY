#include "PreCompile.h"
#include "MapBase.h"
#include <EngineCore/SpriteRenderer.h>

AMapBase::AMapBase()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("MapRenderer");
}

AMapBase::~AMapBase()
{
}

void AMapBase::BeginPlay()
{
	Super::BeginPlay();
}

void AMapBase::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AMapBase::SetMapFile(std::string_view _MapFileName)
{
	Renderer->SetSprite(_MapFileName);
}

void AMapBase::SetMapScale(FVector _Scale)
{
	SetActorScale3D(_Scale);
}

void AMapBase::SetAutoScale()
{
#ifdef _DEBUG
	if (nullptr == Renderer) {
		MsgBoxAssert("Map의 스케일을 지정할 참고 사이즈를 가진 랜더러가 존재하지 않습니다.");
		return;
	}
#endif // _DEBUG
	Renderer->SetAutoSize(1.0f, true);
}