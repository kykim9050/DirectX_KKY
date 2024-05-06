#pragma once
#include <EngineCore/GameMode.h>

// Ό³Έν :
class ALoadingMode : public AGameMode
{
	GENERATED_BODY(AGameMode)
public:
	// constrcuter destructer
	ALoadingMode();
	~ALoadingMode();

	// delete Function
	ALoadingMode(const ALoadingMode& _Other) = delete;
	ALoadingMode(ALoadingMode&& _Other) noexcept = delete;
	ALoadingMode& operator=(const ALoadingMode& _Other) = delete;
	ALoadingMode& operator=(ALoadingMode&& _Other) noexcept = delete;

protected:

private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void LevelEnd(ULevel* _NextLevel) override;
	void LevelStart(ULevel* _PrevLevel) override;
};

