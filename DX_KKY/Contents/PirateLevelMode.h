#pragma once
#include <EngineCore/GameMode.h>
#include <EngineCore/StateManager.h>

// Ό³Έν :
class ACaptainBrineybeardPhase2;
class ACaptainBrineybeardPhase1;
class UTimeScaleControlUnit;
class UCamera;
class UImage;
class AMapBase;
class APlayer;
class AMessage;
class APirateLevelMap;
class ABarrel;
class UPirateLevelDebugWindow;
class APirateLevelMode : public AGameMode
{
	GENERATED_BODY(AGameMode)

public:
	// constrcuter destructer
	APirateLevelMode();
	~APirateLevelMode();

	// delete Function
	APirateLevelMode(const APirateLevelMode& _Other) = delete;
	APirateLevelMode(APirateLevelMode&& _Other) noexcept = delete;
	APirateLevelMode& operator=(const APirateLevelMode& _Other) = delete;
	APirateLevelMode& operator=(APirateLevelMode&& _Other) noexcept = delete;

	static std::shared_ptr<UPirateLevelDebugWindow> DebugWindow;
protected:

private:

	UStateManager ModeState;

	UImage* OldFilm = nullptr;
	UImage* Iris = nullptr;

	std::shared_ptr<UCamera> Camera = nullptr;

	std::shared_ptr<APlayer> Player = nullptr;
	std::shared_ptr<APirateLevelMap> Map = nullptr;
	std::shared_ptr<ACaptainBrineybeardPhase1> Phase1_Boss = nullptr;
	std::shared_ptr<ACaptainBrineybeardPhase2> Phase2_Boss = nullptr;
	std::shared_ptr<ABarrel> Barrel = nullptr;

	std::shared_ptr<AMessage> ScreenMsg = nullptr;

	std::shared_ptr<UTimeScaleControlUnit> TimeControlUnit = nullptr;

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
	void DeleteObject();

	void Phase1(float _DeltaTime);
	void Phase2(float _DeltaTime);

	void ObjectCreate_Shark();
	void ObjectCreate_SeaDog();
};

