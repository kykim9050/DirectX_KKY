#pragma once
#include <EngineCore/GameMode.h>

// Ό³Έν :
class AWorldGameMode : public AGameMode
{
	GENERATED_BODY(AGameMode)

public:
	// constrcuter destructer
	AWorldGameMode();
	~AWorldGameMode();

	// delete Function
	AWorldGameMode(const AWorldGameMode& _Other) = delete;
	AWorldGameMode(AWorldGameMode&& _Other) noexcept = delete;
	AWorldGameMode& operator=(const AWorldGameMode& _Other) = delete;
	AWorldGameMode& operator=(AWorldGameMode&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

