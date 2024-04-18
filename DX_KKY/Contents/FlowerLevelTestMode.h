#pragma once
#include <EngineCore/GameMode.h>

// Ό³Έν :
class AFlowerLevelTestMode : public AGameMode
{
	GENERATED_BODY(AGameMode)

public:
	// constrcuter destructer
	AFlowerLevelTestMode();
	~AFlowerLevelTestMode();

	// delete Function
	AFlowerLevelTestMode(const AFlowerLevelTestMode& _Other) = delete;
	AFlowerLevelTestMode(AFlowerLevelTestMode&& _Other) noexcept = delete;
	AFlowerLevelTestMode& operator=(const AFlowerLevelTestMode& _Other) = delete;
	AFlowerLevelTestMode& operator=(AFlowerLevelTestMode&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelEnd(ULevel* _NextLevel);
	void LevelStart(ULevel* _PrevLevel);

private:

};

