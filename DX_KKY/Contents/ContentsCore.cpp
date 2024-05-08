#include "PreCompile.h"

#include "ContentsCore.h"
#include "LoadingMode.h"


UContentsCore::UContentsCore()
{
}

UContentsCore::~UContentsCore()
{
}

void UContentsCore::Initialize()
{
	LoadingLevelStart();
}

void UContentsCore::LoadingLevelStart()
{
	GEngine->CreateLevel<ALoadingMode>(GLevelName::LoadingLevel);
	GEngine->ChangeLevel(GLevelName::LoadingLevel);
}