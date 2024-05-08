#include "PreCompile.h"
#include <EngineCore/EngineSprite.h>
#include <EngineCore/EngineEditorGUI.h>

#include "ContentsCore.h"
#include "TitleMode.h"
#include "EndingMode.h"
#include "TutorialMode.h"
#include "WorldGameMode.h"
#include "FlowerLevelMode.h"
#include "ContentsDebugWindow.h"
#include "PirateLevelMode.h"
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
	DebugWindow = UEngineEditorGUI::CreateEditorWindow<UContentsDebugWindow>("ContentsDebugWindow");

	ResourceLoad();
	CreateAllLevel();
	GEngine->ChangeLevel(GLevelName::TitleLevel);
}

void UContentsCore::ResourceLoad()
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

	// 이미지 커팅
	{
		UEngineSprite::CreateCutting("Barrel_Normal_Idle.png", 6, 2);
		UEngineSprite::CreateCutting("Pirate_Barrel_AttWait_Idle.png", 6, 2);
		UEngineSprite::CreateCutting("Pirate_Barrel_Drop.png", 4, 1);
		UEngineSprite::CreateCutting("Pirate_Barrel_Smash.png", 5, 1);
		UEngineSprite::CreateCutting("Pirate_Barrel_BackUp.png", 6, 1);
		UEngineSprite::CreateCutting("Barrel_Smash_Dust.png", 8, 3);
		UEngineSprite::CreateCutting("Barrel_Smash_FX.png", 6, 2);
		UEngineSprite::CreateCutting("Shark_Fin.png", 3, 1);
		UEngineSprite::CreateCutting("Shark_Appear.png", 6, 1);
		UEngineSprite::CreateCutting("Shark_Chomp1.png", 5, 2);
		UEngineSprite::CreateCutting("Shark_Chomp2.png", 3, 1);
		UEngineSprite::CreateCutting("Shark_Leave.png", 8, 1);
		UEngineSprite::CreateCutting("Shark_Appear_Effect.png", 11, 2);

		UEngineSprite::CreateCutting("SeaDog_Appear.png", 11, 2);
		UEngineSprite::CreateCutting("SeaDog_Appear_Effect.png", 6, 2);
		UEngineSprite::CreateCutting("SeaDog_Death.png", 8, 1);
		UEngineSprite::CreateCutting("SeaDog_Death_Effect.png", 5, 2);
		UEngineSprite::CreateCutting("SeaDog_Move.png", 6, 2);
		UEngineSprite::CreateCutting("SeaDog_Periscope.png", 10, 5);

		UEngineSprite::CreateCutting("FloralFury_Garden.png", 3, 1);
		UEngineSprite::CreateCutting("ShootinNLootin_Ripples.png", 3, 1);
		UEngineSprite::CreateCutting("ShootinNLootin_Ship.png", 3, 1);
	}
}

void UContentsCore::CreateAllLevel()
{
	GEngine->CreateLevel<ATitleMode>(GLevelName::TitleLevel);
	GEngine->CreateLevel<AEndingMode>(GLevelName::EndingLevel);
	//GEngine->CreateLevel<ATutorialMode>("TutorialLevel");
	GEngine->CreateLevel<AWorldGameMode>(GLevelName::WorldLevel);
	GEngine->CreateLevel<AFlowerLevelMode>(GLevelName::FlowerLevel);
	GEngine->CreateLevel<APirateLevelMode>(GLevelName::PirateLevel);
	GEngine->CreateLevel<ALoadingMode>(GLevelName::LoadingLevel);

}