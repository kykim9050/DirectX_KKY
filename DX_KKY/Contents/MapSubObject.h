#pragma once
#include "MapBase.h"

// Ό³Έν :
class AMapSubObject : public AMapBase
{
	GENERATED_BODY(AMapBase)

public:
	// constrcuter destructer
	AMapSubObject();
	~AMapSubObject();

	// delete Function
	AMapSubObject(const AMapSubObject& _Other) = delete;
	AMapSubObject(AMapSubObject&& _Other) noexcept = delete;
	AMapSubObject& operator=(const AMapSubObject& _Other) = delete;
	AMapSubObject& operator=(AMapSubObject&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

