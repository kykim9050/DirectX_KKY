#include "PreCompile.h"

#include "MonsterUnit.h"

AMonsterUnit::AMonsterUnit()
{
}

AMonsterUnit::~AMonsterUnit()
{
}

void AMonsterUnit::BeginPlay()
{
	Super::BeginPlay();
}

void AMonsterUnit::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == GetHitUse)
	{
		if (nullptr == GetHitFunction)
		{
			MsgBoxAssert("GetHitFunctiondl �������� �ʾҽ��ϴ�.");
			return;
		}

		GetHitFunction();
	}
}