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
		MsgBoxAssert("Map�� �������� ������ ���� ����� ���� �������� �������� �ʽ��ϴ�.");
		return;
	}
#endif // _DEBUG
	Renderer->SetAutoSize(1.0f, true);
}