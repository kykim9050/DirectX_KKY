#pragma once
#include <EngineCore/GameMode.h>

// Ό³Έν :
class LoadingMode : public AGameMode
{
	GENERATED_BODY(AGameMode)
public:
	// constrcuter destructer
	LoadingMode();
	~LoadingMode();

	// delete Function
	LoadingMode(const LoadingMode& _Other) = delete;
	LoadingMode(LoadingMode&& _Other) noexcept = delete;
	LoadingMode& operator=(const LoadingMode& _Other) = delete;
	LoadingMode& operator=(LoadingMode&& _Other) noexcept = delete;

protected:

private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void LevelEnd(ULevel* _NextLevel) override;
	void LevelStart(ULevel* _PrevLevel) override;
};

