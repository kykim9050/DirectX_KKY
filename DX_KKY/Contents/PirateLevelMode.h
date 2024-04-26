#pragma once
#include <EngineCore/GameMode.h>

// Ό³Έν :
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

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelEnd(ULevel* _NextLevel);
	void LevelStart(ULevel* _PrevLevel);
};

