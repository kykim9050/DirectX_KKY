#pragma once
#include <EngineCore/GameMode.h>

// ���� :
class UTimeScaleControlUnit;
class UCamera;
class UImage;
class AMapBase;
class APlayer;
class AMessage;
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

protected:

private:
	UImage* OldFilm = nullptr;
	UImage* Iris = nullptr;

	std::shared_ptr<UCamera> Camera = nullptr;
	std::shared_ptr<AMapBase> Map = nullptr;

	std::shared_ptr<APlayer> Player = nullptr;

	std::shared_ptr<AMessage> ScreenMsg = nullptr;



	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void LevelEnd(ULevel* _NextLevel) override;
	void LevelStart(ULevel* _PrevLevel) override;

	void WidgetInit();
};
