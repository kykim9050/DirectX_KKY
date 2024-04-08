#pragma once
#include "MapBase.h"

// Ό³Έν :
class AWorldMap : public AMapBase
{
	GENERATED_BODY(AMapBase)

public:
	// constrcuter destructer
	AWorldMap();
	~AWorldMap();

	// delete Function
	AWorldMap(const AWorldMap& _Other) = delete;
	AWorldMap(AWorldMap&& _Other) noexcept = delete;
	AWorldMap& operator=(const AWorldMap& _Other) = delete;
	AWorldMap& operator=(AWorldMap&& _Other) noexcept = delete;

protected:

private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

};

