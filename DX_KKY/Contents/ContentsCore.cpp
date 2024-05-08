#include "PreCompile.h"
#include <EngineCore/EngineSprite.h>
#include <EngineCore/EngineEditorGUI.h>

#include "ContentsCore.h"
#include "ContentsDebugWindow.h"
#include "LoadingMode.h"


#include "TestGameMode.h"


UContentsCore::UContentsCore()
{
}

UContentsCore::~UContentsCore()
{
}

void UContentsCore::Initialize()
{
	CreateDebugWindow();
	LoadingLevelStart();
}



void UContentsCore::LoadingLevelStart()
{
	GEngine->CreateLevel<ALoadingMode>(GLevelName::LoadingLevel);
	GEngine->ChangeLevel(GLevelName::LoadingLevel);
}

void UContentsCore::CreateDebugWindow()
{
	DebugWindow = UEngineEditorGUI::CreateEditorWindow<UContentsDebugWindow>("ContentsDebugWindow");
}



