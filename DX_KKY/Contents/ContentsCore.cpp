#include "PreCompile.h"
#include <EngineCore/EngineSprite.h>

#include "ContentsCore.h"
#include "TitleMode.h"
#include "EndingMode.h"
#include "TutorialMode.h"
#include "WorldGameMode.h"

#include "TestGameMode.h"
#include "FlowerLevelMode.h"


UContentsCore::UContentsCore()
{
}

UContentsCore::~UContentsCore()
{
}

void UContentsCore::Initialize()
{
	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("ContentsResources");
		Dir.Move("Image");
		std::vector<UEngineFile> Files = Dir.GetAllFile({ ".png" }, true);
		for (UEngineFile& File : Files)
		{
			UEngineSprite::Load(File.GetFullPath());
		}
	}

	{	
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("ContentsResources");
		Dir.Move("Image");
		std::vector<UEngineDirectory> Directorys = Dir.GetAllDirectory(true);
		for (size_t i = 0; i < Directorys.size(); i++)
		{
			std::string Name = Directorys[i].GetFolderName();
			UEngineSprite::LoadFolder(Directorys[i].GetFullPath());
		}
	}

	GEngine->CreateLevel<ATitleMode>("TitleLevel");
	GEngine->CreateLevel<AEndingMode>("EndingLevel");
	GEngine->CreateLevel<ATutorialMode>("TutorialLevel");
	GEngine->CreateLevel<AWorldGameMode>("WorldLevel");
	GEngine->CreateLevel<ATestGameMode>("TestLevel");
	GEngine->CreateLevel<AFlowerLevelMode>("FlowerLevel");
	GEngine->ChangeLevel("FlowerLevel");
}

