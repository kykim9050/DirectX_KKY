#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class APirateLevelMap : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constrcuter destructer
	APirateLevelMap();
	~APirateLevelMap();

	// delete Function
	APirateLevelMap(const APirateLevelMap& _Other) = delete;
	APirateLevelMap(APirateLevelMap&& _Other) noexcept = delete;
	APirateLevelMap& operator=(const APirateLevelMap& _Other) = delete;
	APirateLevelMap& operator=(APirateLevelMap&& _Other) noexcept = delete;

protected:

private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
};

