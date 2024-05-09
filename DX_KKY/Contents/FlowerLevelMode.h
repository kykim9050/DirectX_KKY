#pragma once
#include <EngineCore/GameMode.h>
#include <EngineCore/StateManager.h>

// Ό³Έν :
class UEngineRandom;
class UFlowerLevelDebugWindow;
class UTimeScaleControlUnit;
class AMessage;
class APlatformShadow;
class AFlowerPlatform;
class UCamera;
class UImage;
class APlayer;
class ACagneyCarnation;
class AMapBase;
class AFlowerLevelMode : public AGameMode
{
	GENERATED_BODY(AGameMode)

public:
	// constrcuter destructer
	AFlowerLevelMode();
	~AFlowerLevelMode();

	// delete Function
	AFlowerLevelMode(const AFlowerLevelMode& _Other) = delete;
	AFlowerLevelMode(AFlowerLevelMode&& _Other) noexcept = delete;
	AFlowerLevelMode& operator=(const AFlowerLevelMode& _Other) = delete;
	AFlowerLevelMode& operator=(AFlowerLevelMode&& _Other) noexcept = delete;

	static std::shared_ptr<UFlowerLevelDebugWindow> DebugWindow;

protected:


private:
	UStateManager ModeState;

	UImage* OldFilm = nullptr;
	UImage* Iris = nullptr;
	int ShadowNum = 3;

	std::shared_ptr<UCamera> Camera = nullptr;

	std::shared_ptr<APlayer> Player = nullptr;
	std::shared_ptr<ACagneyCarnation> BossMonster = nullptr;
	std::shared_ptr<AMapBase> MapFrontObject = nullptr;
	std::shared_ptr<AMapBase> Map = nullptr;
	std::shared_ptr<AMapBase> BackGroundObject = nullptr;
	std::shared_ptr<AMapBase> ColMap = nullptr;

	std::shared_ptr<AFlowerPlatform> Platform1 = nullptr;
	std::shared_ptr<AFlowerPlatform> Platform2 = nullptr;
	std::shared_ptr<AFlowerPlatform> Platform3 = nullptr;
	std::vector<std::shared_ptr<APlatformShadow>> Shadows;
	std::shared_ptr<AMessage> ScreenMsg = nullptr;

	std::shared_ptr<UTimeScaleControlUnit> TimeControlUnit = nullptr;

	std::shared_ptr<UEngineRandom> Random;
	
	UEngineSoundPlayer BGMPlayer = UEngineSoundPlayer();

private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void LevelEnd(ULevel* _NextLevel) override;
	void LevelStart(ULevel* _PrevLevel) override;
	void StateInit();

	void WidgetInit();
	void CreateObject();
	void ObjectInit();
	void ObjectDelete();

	void Phase1(float _DeltaTime);
};

