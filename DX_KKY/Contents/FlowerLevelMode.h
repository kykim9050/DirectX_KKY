#pragma once
#include <EngineCore/GameMode.h>

// Ό³Έν :
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

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelEnd(ULevel* _NextLevel);
	void LevelStart(ULevel* _PrevLevel);

private:

};

